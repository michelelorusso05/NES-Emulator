// Mapper 011

#include "mapper.hpp"

class Mapper011 : public Mapper 
{
public:
    Mapper011(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        reset();
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            mappedAddr = ((bankSelect & 0x03) << 15) | (addr & 0x7FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            bankSelect = data;

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        if (addr >= 0x0000 && addr <= 0x1FFF)
        {
            mappedAddr = ((bankSelect >> 4) << 13) | (addr & 0x1FFF);
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
        return "COLORDREAMS";
    }

    void reset() override
    {
        bankSelect = 0;
    }

private:
    uint8_t bankSelect = 0;
};