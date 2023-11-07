// Mapper 099

// This mapper is used by VS-System games.
// It provides 2KB of RAM where SRAM would normally be
// and also has four-windows mirroring.

#include "mapper.hpp"

class Mapper099 : public Mapper 
{
public:
    Mapper099(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, Mapper::Arrangement::FOUR_SCREENS)
    {
        prgRam = persistentMemory;

        additionalWindow0.fill(0);
        additionalWindow1.fill(0);
    }

    std::array<uint8_t, 1024>* GetAdditionalWindowRam(uint8_t window) override
    {
        return (window == 0) ? &additionalWindow0 : &additionalWindow1;
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
            mappedAddr = (addr & 0x7FFF);
            return true;
        }
        if (addr >= 0x8000 && addr <= 0x9FFF)
        {
            mappedAddr = ((bankSelect << 12) | (addr & 0x1FFF));
            return true;
        }
        if (addr >= 0xA000 && addr <= 0xFFFF)
        {
            mappedAddr = (addr & 0x7FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr == 0x4016)
        {
            bankSelect = ((data & 0x04) > 0);

            // Data still needs to go to the controller management system
            return false;
        }
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
            mappedAddr = ((bankSelect << 12) | addr);
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
        return "VS Unisystem";
    }
private:
    std::vector<uint8_t>* prgRam;
    uint8_t bankSelect = 1;

    std::array<uint8_t, 1024> additionalWindow0;
    std::array<uint8_t, 1024> additionalWindow1;
};