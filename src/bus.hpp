#pragma once

#include <cstdint>
#include <array>

#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "cartridge.hpp"
#include "controller.hpp"

#include <atomic>
#include <queue>

// Sizes
#define SIZE_INTERNAL_RAM       0x0800
#define SIZE_PPU_IO             0x0008
#define SIZE_APU_IO             0x0018
#define SIZE_CARTRIDGE_ROM      0xBFDF

// Offsets
#define OFFSET_INTERNAL_RAM     0x0000
#define OFFSET_PPU_IO           0x2000
#define OFFSET_APU_IO           0x4000
#define OFFSET_CARTRIDGE_ROM    0x4020

// Ports
#define PORT_PPU_DMA            0x4014

// Clock
#define MASTER_CLOCK            236.25f * 1000000 / (11)
#define PPU_DIVIDER             4

#define AUDIO_BUFFER_SIZE       512

class Bus
{
public:
    // Devices
    CPU cpu = CPU(this);
    PPU ppu = PPU(this);
    APU apu;

    Controller player1;
    Controller player2;
    bool refreshControllers = false;

    std::array<uint8_t, 2 * 1024> wRam;
    Cartridge* rom = nullptr;

    bool isRomLoaded = false;

    Bus()
    {
        for (uint8_t& i : wRam)
            i = 0; 
    }

    void LoadRom(Cartridge* data)
    {
        rom = data;
        ppu.LoadCartridge(data);
        isRomLoaded = true;
        reset();
    }

    // Memory pointed by the pointer must be unallocated manually
    void UnloadRom()
    {
        isRomLoaded = false;
        rom = nullptr;
        ppu.UnloadCartridge();
    }

    void SetButtonStatus(Controller::Buttons b, bool set)
    {
        player1.SetButton(b, set);
    }

    // Memory map and registers can be found on NesDEV
    // https://www.nesdev.org/wiki/CPU_memory_map
    // https://www.nesdev.org/wiki/2A03
    void write(uint16_t addr, uint8_t data)
    {
        // Cartridge has priority
        if (isRomLoaded && rom->cpuWrite(addr, data))
        {
            // Cartridge can intercept writes to every address, according to the mapper needs
            return;
        }
        
        // Memory and mirrors
        if (addr >= OFFSET_INTERNAL_RAM && addr < OFFSET_INTERNAL_RAM + SIZE_INTERNAL_RAM * 4)
        {
            wRam.at(addr & (SIZE_INTERNAL_RAM - 1)) = data;
            return;
        }
        // PPU I/O and mirrors
        if (addr >= OFFSET_PPU_IO && addr < OFFSET_PPU_IO + SIZE_PPU_IO * 1024)
        {
            uint8_t reg = addr & (SIZE_PPU_IO - 1);
            ppu.writeRegisters(reg, data);
            return;
        }

        // PPU DMA
        if (addr == PORT_PPU_DMA)
        {
            ppu.writeRegisters(0x14, data);
            return;
        }

        // Joystick strobe
        if (addr == 0x4016)
        {
            refreshControllers = (data & 0x01 == 1);
            if (refreshControllers)
                player1.Transfer();
            return;
        }

        if (addr >= 0x4000 && addr <= 0x4017)
        {
            apu.writeRegisters(addr & 0x1F, data);
            return;
        }
    }
    uint8_t read(uint16_t addr)
    {
        // Cartridge has priority
        if (isRomLoaded && rom->cpuRead(addr, fetched))
        {
            // Cartridge can intercept writes to every address, according to the mapper needs
            return fetched;
        }

        if (addr >= OFFSET_INTERNAL_RAM && addr < OFFSET_INTERNAL_RAM + SIZE_INTERNAL_RAM * 4)
            return wRam.at(addr & (SIZE_INTERNAL_RAM - 1));
        
        if (addr >= OFFSET_PPU_IO && addr < OFFSET_PPU_IO + SIZE_PPU_IO * 1024)
        {
            uint8_t reg = addr & (SIZE_PPU_IO - 1);
            return ppu.readRegisters(reg);
        }

        if (addr == PORT_PPU_DMA)
        {
            return ppu.readRegisters(0x14);
        }

        if (addr == 0x4016)
        {
            return player1.Read();
        }
        if (addr == 0x4017)
        {
            return player2.Read();
        }

        if (addr >= 0x4000 && addr <= 0x4015)
        {
            return apu.readRegisters(addr & 0x1F);
        }

        return 0x00;
    }

    // Returns true if this clock reached audio syncronization
    bool busClock()
    {    
        ppu.clock();
        apu.clock();

        if (ppu.checkNMI())
        {
            cpu.nmiPending = true;
        }
        else
        {
            cpu.nmiPending = false;
        }
        
        if (totalClockCycles % 3 == 0)
            cpu.clock();



        if (rom != nullptr && rom->checkIRQ())
        {
            rom->resetIRQ();
            cpu.irq();
        }
        
        if (apu.irq)
        {
            cpu.irq();
        }

        bool audioSync = false;
        elapsedAudioTime += timePerNESClock;

        if (elapsedAudioTime >= audioPeriod)
        {
            elapsedAudioTime -= audioPeriod;
            lastGeneratedAudioSample = apu.getOutput();

            while (mutex);
            mutex = true;
            audioBuffer.push(lastGeneratedAudioSample * 60000);
            mutex = false;

            if (audioPointer++ > 512)
                init = true;

            /*
            currentBuffer[audioPointer++] = lastGeneratedAudioSample * 60000;

            if (audioPointer == AUDIO_BUFFER_SIZE)
            {
                audioPointer = 0;
                init = true;
                filled = true;

                if (currentBuffer == buf0)
                {
                    currentBuffer = buf1;
                    usableBuffer = buf0;
                }
                else
                {
                    currentBuffer = buf0;
                    usableBuffer = buf1;
                }
                
            }
            */
            audioSync = true;
        }
        
        totalClockCycles++;

        return audioSync;
    }

    void reset()
    {
        cpu.reset();
        ppu.reset();
        apu.reset();
        totalClockCycles = 0;

        wRam.fill(0);
    }

    void SetAudioFrequency(double frequency)
    {
        audioPeriod = 1.0 / frequency;
    }
    
    double lastGeneratedAudioSample = 0;

    volatile bool init = false;

    std::atomic_bool filled = {false};
    std::atomic_bool mutex = {false};

    uint16_t* buf0 = new uint16_t[AUDIO_BUFFER_SIZE];
    uint16_t* buf1 = new uint16_t[AUDIO_BUFFER_SIZE];

    uint16_t* currentBuffer = buf0;
    uint16_t* usableBuffer = buf1;

    std::queue<uint16_t> audioBuffer;

private:
    uint8_t fetched;
    uint64_t totalClockCycles = 0;

    double audioPeriod;
    // NTSC crystal timing
    const double timePerNESClock = 1.0 / 5369318.0;
    double elapsedAudioTime = 0;

    uint64_t audioPointer = 0;
};