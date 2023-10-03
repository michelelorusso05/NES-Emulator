// Mapper 009

#include "mapper.hpp"

class Mapper009 : public Mapper 
{
public:
    Mapper009(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        prgWindows = (pBanks << 1);
        prgRam = persistentMemory;
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x6000 && addr <= 0x7FFF)
        {
            // Read to PRG-RAM
            data = prgRam->at(addr & 0x1FFF);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0x8000 && addr <= 0x9FFF)
        {
            mappedAddr = (prgRomBank << 13) | (addr & 0x1FFF);
            return true;
        }
        if (addr >= 0xA000 && addr <= 0xFFFF)
        {
            // Fix the last 4 banks instead of 3. 
            // The first of these banks is address-shadowed by the switchable bank, so it won't be accessible.
            mappedAddr = ((prgWindows - 4) << 13) | (addr & 0x7FFF);
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
        // PRG-ROM bank select
        if (addr >= 0xA000 && addr <= 0xAFFF)
        {
            prgRomBank = (data & 0x0F);

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        // CHR-ROM 0xFD/0000 bank select
        if (addr >= 0xB000 && addr <= 0xBFFF)
        {
            fd0000bankSelect = (data & 0x1F);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        // CHR-ROM 0xFE/0000 bank select
        if (addr >= 0xC000 && addr <= 0xCFFF)
        {
            fe0000bankSelect = (data & 0x1F);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        // CHR-ROM 0xFD/1000 bank select
        if (addr >= 0xD000 && addr <= 0xDFFF)
        {
            fd1000bankSelect = (data & 0x1F);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        // CHR-ROM 0xFE/1000 bank select
        if (addr >= 0xE000 && addr <= 0xEFFF)
        {
            fe1000bankSelect = (data & 0x1F);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        // Mirroring
        if (addr >= 0xF000 && addr <= 0xFFFF)
        {
            // 0 -> vertical mirroring, aka horizontal arrangement
            // 1 -> horizontal mirroring, aka vertical arrangement
            // Horizontal and vertical are swapped in the enum, so the data byte is NOTted
            arrangement = (Arrangement) (~data & 0x01);
            arrangementUpdated = true;

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        bool mapped = false;
        if (addr >= 0x0000 && addr <= 0x0FFF)
        {
            if (latch0 == 0xFD)
            {
                mappedAddr = (fd0000bankSelect << 12) | (addr & 0x0FFF);
            }
            else
            {
                mappedAddr = (fe0000bankSelect << 12) | (addr & 0x0FFF);
            }
            mapped = true;
        }
        else if (addr >= 0x1000 && addr <= 0x1FFF)
        {
            if (latch1 == 0xFD)
            {
                mappedAddr = (fd1000bankSelect << 12) | (addr & 0x0FFF);
            }
            else
            {
                mappedAddr = (fe1000bankSelect << 12) | (addr & 0x0FFF);
            }
            mapped = true;
        }

        if (addr == 0x0FD8)
            latch0 = 0xFD;
        else if (addr == 0x0FE8)
            latch0 = 0xFE;
        else if (addr >= 0x1FD8 && addr <= 0x1FDF)
            latch1 = 0xFD;
        else if (addr >= 0x1FE8 && addr <= 0x1FEF)
            latch1 = 0xFE;
        return mapped;
    }
    bool chrBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (cBanks == 0 && addr >= 0x0000 && addr <= 0x1FFF)
        {
            mappedAddr = addr;
            return true;
        }
        return false;
    }

    std::string getMapperName() override
    {
        return "PxROM (MMC2)";
    }

private:
    std::vector<uint8_t>* prgRam;

    uint8_t prgRomBank = 0;
    uint8_t prgWindows;

    uint8_t fd0000bankSelect = 0;
    uint8_t fe0000bankSelect = 0;
    uint8_t fd1000bankSelect = 0;
    uint8_t fe1000bankSelect = 0;

    uint8_t latch0 = 0xFD;
    uint8_t latch1 = 0xFD;
};