// Mapper 028

#include "mapper.hpp"

class Mapper028 : public Mapper 
{
public:
    Mapper028(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        reset();
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            uint8_t cpuA14 = ((addr >> 14) & 0x01);
            uint8_t outerBank = (regOuterBank << 1);
            uint8_t innerBank = regInnerBank;
            // Discard mirroring bits
            uint8_t bankMode = (regMode >> 2);
            // Is in UNROM fixed bank?
            if (((bankMode ^ cpuA14) & 0x03) == 0x02)
            {
                // Treat as NROM
                bankMode = 0;
            }
            // Is in 32KB bank mode?
            if ((bankMode & 0x02) == 0)
            {
                innerBank = ((innerBank << 1) | cpuA14);
            }
            uint8_t bankSizeMask = bankSizeMasks[(bankMode >> 2) & 0x03];
            mappedAddr = (((innerBank & bankSizeMask) | (outerBank & ~bankSizeMask)) << 14) | (addr & 0x3FFF);
            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x5000 && addr <= 0x5FFF)
        {
            registerSelect = data;

            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }
        if (addr >= 0x8000 && addr <= 0xFFFF)
        {
            switch (registerSelect)
            {
                case 0x00:
                    regChrBank = data;

                    if (regMode & 0x02 == 0)
                    {
                        arrangement = (((regChrBank & 0x10) == 0) ? ONE_SCREEN_A : ONE_SCREEN_B);
                        arrangementUpdated = true;
                    }
                    break;
                case 0x01:
                    regInnerBank = data;

                    if (regMode & 0x02 == 0)
                    {
                        arrangement = (((regChrBank & 0x10) == 0) ? ONE_SCREEN_A : ONE_SCREEN_B);
                        arrangementUpdated = true;
                    }

                    break;
                case 0x80:
                    regMode = data;
                    switch (regMode & 0x03)
                    {
                        case 0:
                            arrangement = ONE_SCREEN_A;
                            break;
                        case 1:
                            arrangement = ONE_SCREEN_B;
                            break;
                        case 2:
                            arrangement = HORIZONTAL;
                            break;
                        case 3:
                            arrangement = VERTICAL;
                            break;
                    }
                    arrangementUpdated = true;
                    break;
                case 0x81:
                    regOuterBank = data;
                    break;
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
            mappedAddr = (((regChrBank & 0x03) << 13) | (addr & 0x1FFF));
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
        return "INL-ROM (A53)";
    }

    void reset() override
    {

    }
private:
    uint8_t registerSelect = 0;

    uint8_t regChrBank = 0xFF;
    uint8_t regInnerBank = 0xFF;
    uint8_t regMode = 0xFF;
    uint8_t regOuterBank = 0xFF;

    uint8_t bankSizeMasks[4] =
    {
        0x01,
        0x03,
        0x07,
        0x0F
    };
};