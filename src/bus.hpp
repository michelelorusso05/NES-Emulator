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

#include "circularBuffer.hpp"

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

// Audio constants
#define SAMPLING_FREQUENCY      48000
#define MS_LATENCY              60
const int AUDIO_BUFFER_SIZE = (MS_LATENCY / 1000.0f) * SAMPLING_FREQUENCY * 2;

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

        audioBuffer.Init(AUDIO_BUFFER_SIZE);
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

    void SetButtonStatusPlayer1(Controller::Buttons b, bool set)
    {
        player1.SetButton(b, set);
    }
    void SetButtonStatusPlayer2(Controller::Buttons b, bool set)
    {
        player2.SetButton(b, set);
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
            {
                player1.Transfer();
                player2.Transfer();
            }
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

        
        // Famicom disk system registers (FDS is not implemneted)
        if (addr == 0x4032)
        {
            // Report as disk not inserted
            return 0x07;
        }
        if (addr == 0x4033)
        {
            // Report good battery voltage
            return 0x80;
        }
        
    
        return 0x00;
    }

    // Returns true if this clock reached audio syncronization
    bool busClock()
    {    
        bool frameComplete = ppu.clock();
    
        if (ppu.checkNMI())
        {
            cpu.nmiPending = true;
        }
        else
        {
            cpu.nmiPending = false;
        }
        
        if (totalClockCycles % 3 == 0)
        {
            apu.clock();
            cpu.clock();

            if (rom != nullptr)
                rom->sendExternalEvent(0x01);
        }

        if (rom != nullptr && rom->checkIRQ())
        {
            rom->resetIRQ();
            cpu.irq();
        }
        
        if (apu.irq)
        {
            cpu.irq();
        }

        elapsedAudioTime += timePerNESClock;

        if (elapsedAudioTime >= audioPeriod)
        {
            elapsedAudioTime -= audioPeriod;
            lastGeneratedAudioSample = apu.getOutput();
            while (mutex);
            audioBuffer.PushBack(lastGeneratedAudioSample * 32767);
            //audioBuffer.push(lastGeneratedAudioSample * 32767);
        }
        
        totalClockCycles++;

        return frameComplete;
    }

    void reset()
    {
        cpu.reset();
        ppu.reset();
        apu.reset();
        if (rom != nullptr)
            rom->reset();
        totalClockCycles = 0;

        wRam.fill(0);
    }

    void SetAudioFrequency(double frequency)
    {
        audioPeriod = 1.0 / frequency;
    }
    
    double lastGeneratedAudioSample = 0;

    // std::queue<int16_t> audioBuffer;
    CircularBuffer<int16_t> audioBuffer;
    volatile bool mutex = false;

private:
    uint8_t fetched;
    uint64_t totalClockCycles = 0;

    double audioPeriod;
    // NTSC crystal timing
    const double timePerNESClock = 1.0 / 5369318.0;
    double elapsedAudioTime = 0;
};