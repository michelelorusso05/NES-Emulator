// Mapper 004

#include "mapper.hpp"

class Mapper004 : public Mapper 
{
public:
    Mapper004(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        prgWindows = prgBanks << 1;
        prgRam = persistentMemory;

        reset();
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x6000 && addr <= 0x7FFF)
        {
            // Read from PRG-RAM
            data = prgRam->at(addr & 0x1FFF);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            mappedAddr = (prgBankOffsets[(addr & 0x7FFF) >> 13] | (addr & 0x1FFF));
            return true;
        }
        
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x6000 && addr <= 0x7FFF)
        {
            // Write to PRG-RAM
            prgRam->at(addr & 0x1FFF) = data;
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0x8000 && addr <= 0x9FFF)
        {
            // Odd - Bank data
            if (addr & 0x01)
            {
                registers[bankSelect & 0x07] = data;

                // CHR A12 inversion
                if (bankSelect & 0x80)
                {
                    chrBankOffsets[0] = (registers[2] << 10);
                    chrBankOffsets[1] = (registers[3] << 10);
                    chrBankOffsets[2] = (registers[4] << 10);
                    chrBankOffsets[3] = (registers[5] << 10);

                    chrBankOffsets[4] = ((registers[0] & 0xFE) << 10);
                    chrBankOffsets[5] = (((registers[0] & 0xFE) << 10) | 0x0400);

                    chrBankOffsets[6] = ((registers[1] & 0xFE) << 10);
                    chrBankOffsets[7] = (((registers[1] & 0xFE) << 10) | 0x0400);
                }
                else
                {
                    chrBankOffsets[0] = ((registers[0] & 0xFE) << 10);
                    chrBankOffsets[1] = (((registers[0] & 0xFE) << 10) | 0x0400);

                    chrBankOffsets[2] = ((registers[1] & 0xFE) << 10);
                    chrBankOffsets[3] = (((registers[1] & 0xFE) << 10) | 0x0400);

                    chrBankOffsets[4] = (registers[2] << 10);
                    chrBankOffsets[5] = (registers[3] << 10);
                    chrBankOffsets[6] = (registers[4] << 10);
                    chrBankOffsets[7] = (registers[5] << 10);
                }

                if (bankSelect & 0x40)
                {
                    prgBankOffsets[0] = ((prgWindows - 2) << 13); 
                    prgBankOffsets[1] = (registers[7] << 13);
                    prgBankOffsets[2] = (registers[6] << 13);
                    prgBankOffsets[3] = ((prgWindows - 1) << 13);
                }
                else
                {
                    prgBankOffsets[0] = (registers[6] << 13);
                    prgBankOffsets[1] = (registers[7] << 13);
                    prgBankOffsets[2] = ((prgWindows - 2) << 13);
                    prgBankOffsets[3] = ((prgWindows - 1) << 13);
                }
            }
            // Even - Bank select
            else
            {
                bankSelect = data;
            }

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0xA000 && addr <= 0xBFFF)
        {
            // Odd - PRG-RAM protect
            if (addr & 0x01)
            {
                // TODO
            }
            // Even - Mirroring
            else
            {
                // 0 -> vertical mirroring, aka horizontal arrangement
                // 1 -> horizontal mirroring, aka vertical arrangement
                // Horizontal and vertical are swapped in the enum, so the data byte is NOTted
                arrangement = (Arrangement) (~data & 0x01);
                arrangementUpdated = true;
            }

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0xC000 && addr <= 0xDFFF)
        {
            // Odd - IRQ reload
            if (addr & 0x01)
            {
                irqCounter = 0;
                resetLatch = true;
            }
            // Even - IRQ latch
            else
            {
                irqDefaultValue = data;
            }

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0xE000 && addr <= 0xFFFF)
        {
            // Odd - IRQ enable
            if (addr & 0x01)
            {
                irqEnabled = true;
            }
            // Even - IRQ disable
            else
            {
                irqEnabled = false;
                irqRequested = false;
            }

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }

        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        if (addr >= 0x0000 && addr <= 0x1FFF)
        {
            mappedAddr = chrBankOffsets[addr >> 10] | (addr & 0x03FF);
            return true;
        }
        return false;
    }
    bool chrBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x0000 && addr <= 0x1FFF && cBanks == 0)
        {
            mappedAddr = chrBankOffsets[addr >> 10] | (addr & 0x03FF);
            return true;
        }
        return false;
    }

    bool checkIRQ() override
    {
        return irqRequested;
    }

    void resetIRQ() override
    {
        irqRequested = false;
    }

    void scanlineCallback() override
    {
        if (resetLatch)
        {
            resetLatch = false;
            irqCounter = irqDefaultValue;
        }

        if (irqCounter == 0)
        {
            if (irqEnabled)
                irqRequested = true;

            irqCounter = irqDefaultValue;
        }
        else
            irqCounter--;
    }

    std::string getMapperName() override
    {
        return "TxROM (MMC3)";
    }

    void reset() override
    {
        registers[0] = 0;
        registers[1] = 2;
        registers[2] = 4;
        registers[3] = 5;
        registers[4] = 6;
        registers[5] = 7;
        registers[6] = 0;
        registers[7] = 1;

        chrBankOffsets[0] = ((registers[0] & 0xFE) << 10);
        chrBankOffsets[1] = (((registers[0] & 0xFE) << 10) | 0x0400);

        chrBankOffsets[2] = ((registers[1] & 0xFE) << 10);
        chrBankOffsets[3] = (((registers[1] & 0xFE) << 10) | 0x0400);

        chrBankOffsets[4] = (registers[2] << 10);
        chrBankOffsets[5] = (registers[3] << 10);
        chrBankOffsets[6] = (registers[4] << 10);
        chrBankOffsets[7] = (registers[5] << 10);

        prgBankOffsets[0] = (registers[6] << 13);
        prgBankOffsets[1] = (registers[7] << 13);
        prgBankOffsets[2] = ((prgWindows - 2) << 13);
        prgBankOffsets[3] = ((prgWindows - 1) << 13);
    }

    void receiveExternalEvent(uint8_t ev) override
    {
        if (ev == EVENT_A12_CLOCKED)
            scanlineCallback();
    }

private:
    std::vector<uint8_t>* prgRam;

    bool irqEnabled = false;
    bool irqRequested = false;
    bool resetLatch = false;
    uint8_t irqCounter = 0;
    uint8_t irqDefaultValue = 255;

    uint8_t bankSelect = 0;

    uint8_t prgWindows;

    // 0 - PPU at 0x0000-0x07FF (2KB)
    // 1 - PPU at 0x0800-0x0FFF (2KB)
    // 2 - PPU at 0x1000-0x13FF (1KB)
    // 3 - PPU at 0x1400-0x17FF (1KB)
    // 4 - PPU at 0x1800-0x1BFF (1KB)
    // 5 - PPU at 0x1C00-0x1FFF (1KB)
    // 6 - CPU at 0x8000-0x9FFF (8KB)
    // 7 - CPU at 0xA000-0xBFFF (8KB)
    uint8_t registers[8];

    uint32_t chrBankOffsets[8];
    uint32_t prgBankOffsets[4];

    uint16_t previouslyAccessedAddress = 0;
};