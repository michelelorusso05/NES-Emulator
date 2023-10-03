// Mapper 001

#include "mapper.hpp"

class Mapper001 : public Mapper 
{
public:
    Mapper001(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        control |= 0x0C;
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

        if (addr >= 0x8000)
        {
            // 16KB mode
            if (control & 0x08)
            {
                // Fix last bank, switch other
                if (control & 0x04)
                {
                    if (addr >= 0x8000 && addr <= 0xBFFF)
                    {
                        mappedAddr = ((prgBank & 0x0F) << 14) | (addr & 0x3FFF);
                    }
                    else
                    {
                        mappedAddr = ((pBanks - 1) << 14) | (addr & 0x3FFF);
                    }
                }
                // Fix first bank, switch other
                else
                {
                    if (addr >= 0x8000 && addr <= 0xBFFF)
                    {
                        mappedAddr = addr & 0x3FFF;
                    }
                    else
                    {
                        mappedAddr = ((prgBank & 0x0F) << 14) | addr & 0x3FFF;
                    }
                }
                return true;
            }
            // 32KB mode
            else
            {
                mappedAddr = (((prgBank >> 1) & 0x07) << 15) | (addr & 0x7FFF);
                return true;
            }
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
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            if (data & 0x80)
            {
                internalShiftRegister = 0;
                srWriteCount = 0;
                control |= 0x0C;
            }
            else
            {
                internalShiftRegister >>= 1;
                internalShiftRegister |= ((data & 0x01) << 4);
                srWriteCount++;

                if (srWriteCount == 5)
                {
                    uint8_t registerSelect = ((addr >> 13) & 0x03);
                    
                    switch (registerSelect)
                    {
                        // Control
                        case 0:
                            control = internalShiftRegister & 0x1F;
                            arrangement = controlMapArrangements[control & 0x03];
                            arrangementUpdated = true;
                            break;
                        // CHR0
                        case 1:
                            chrBank0 = internalShiftRegister & 0x1F;
                            break;
                        // CHR1
                        case 2:
                            chrBank1 = internalShiftRegister & 0x1F;
                            break;
                        // PRG
                        case 3:
                            prgBank = internalShiftRegister & 0x1F;
                            break;
                    }

                    srWriteCount = 0;
                    internalShiftRegister = 0;
                }
            }


            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        return false;
    }
    bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override
    {
        if (addr > 0x1FFF)
            return false;

        if (cBanks == 0)
        {
            mappedAddr = addr;
            return true;
        }

        // Switch two 4KB banks
        if (control & 0x10)
        {
            // First 4KB bank
            if (addr >= 0x0000 && addr <= 0x0FFF)
            {
                mappedAddr = ((chrBank0) << 12) | (addr & 0x0FFF);
            }
            // Second 4KB bank
            else if (addr >= 0x1000 && addr <= 0x1FFF)
            {
                mappedAddr = ((chrBank1) << 12) | (addr & 0x0FFF);
            }

            return true;
        }
        // Switch 8KB bank
        else
        {
            mappedAddr = ((chrBank0 >> 1) << 13) | (addr & 0x1FFF);
            return true;
        }
        
        return false;
    }
    bool chrBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (cBanks > 0)
            return false;

        if (addr > 0x1FFF)
            return false;
        // Switch two 4KB banks
        if (control & 0x10)
        {
            // First 4KB bank
            if (addr >= 0x0000 && addr <= 0x0FFF)
            {
                mappedAddr = ((chrBank0) << 12) | (addr & 0x0FFF);
            }
            // Second 4KB bank
            else if (addr >= 0x1000 && addr <= 0x1FFF)
            {
                mappedAddr = ((chrBank1) << 12) | (addr & 0x0FFF);
            }

            return true;
        }
        // Switch 8KB bank
        else
        {
            mappedAddr = ((chrBank0 >> 1) << 13) | (addr & 0x1FFF);
            return true;
        }
        
        return false;
    }

    std::string getMapperName() override
    {
        return "SxROM (MMC1)";
    }

private:
    std::vector<uint8_t>* prgRam;

    uint8_t internalShiftRegister = 0;
    uint8_t srWriteCount = 0;

    uint8_t control = 0;
    uint8_t chrBank0 = 0;
    uint8_t chrBank1 = 0;
    uint8_t prgBank = 0;

    Arrangement controlMapArrangements[4] =
    {
        ONE_SCREEN_A,
        ONE_SCREEN_B,
        HORIZONTAL,
        VERTICAL
    };
};