// Mapper 000

#include "mapper.hpp"

class Mapper000 : public Mapper 
{
public:
    Mapper000(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        prgRam = persistentMemory;
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
            mappedAddr = pBanks > 1 ? addr & 0x7FFF : addr & 0x3FFF;
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
        return "NROM";
    }
private:
    std::vector<uint8_t>* prgRam;
};