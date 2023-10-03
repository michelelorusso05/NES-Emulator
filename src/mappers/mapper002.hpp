// Mapper 002

#include "mapper.hpp"

class Mapper002 : public Mapper 
{
public:
    Mapper002(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x8000 && addr <= 0xBFFF)
        {
            mappedAddr = (prgRomSelect << 14) | (addr & 0x3FFF);
            return true;
        }
        if (addr >= 0xC000 && addr <= 0xFFFF)
        {
            mappedAddr = ((pBanks - 1) << 14) | (addr & 0x3FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            prgRomSelect = data;

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
        return "UxROM";
    }

private:
    uint8_t prgRomSelect = 0;
};