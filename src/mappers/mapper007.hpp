// Mapper 007

#include "mapper.hpp"

class Mapper007 : public Mapper 
{
public:
    Mapper007(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
        :Mapper(prgBanks, chrBanks, ONE_SCREEN_A)
    {
        reset();
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            mappedAddr = (prgBankOffset << 15) | (addr & 0x7FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            uint8_t newArrangement = ((data & 0x10) > 0);
            if (newArrangement != previousArrangement)
            {
                arrangement = ((newArrangement == 0) ? ONE_SCREEN_A : ONE_SCREEN_B);
                arrangementUpdated = true;
            }
            previousArrangement = newArrangement;

            prgBankOffset = (data & 0x07);

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        if (addr >= 0x0000 && addr <= 0x1FFF)
        {
            mappedAddr = addr;
            return true;
        }
        return false;
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
        return "AxROM";
    }

    void reset() override
    {
        prgBankOffset = ((pBanks >> 1) - 1);
        previousArrangement = 0;

        arrangement = ONE_SCREEN_A;
        arrangementUpdated = true;
    }

private:
    uint8_t prgBankOffset = 0;
    uint8_t previousArrangement = 0;
};