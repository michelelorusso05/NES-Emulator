// Mapper 066

#include "mapper.hpp"

class Mapper066 : public Mapper 
{
public:
    Mapper066(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            mappedAddr = (prgBankSelect << 15) | (addr & 0x7FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            prgBankSelect = ((data >> 4) & 0x03);
            chrBankSelect = (data & 0x03);

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }

        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        if (addr >= 0x0000 && addr <= 0x1FFF)
        {
            mappedAddr = (chrBankSelect << 13) | (addr & 0x1FFF);
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
        return "GxROM";
    }
private:
    uint8_t prgBankSelect = 0;
    uint8_t chrBankSelect = 0;
};