// Mapper 105

#include "mapper.hpp"

class Mapper105 : public Mapper 
{
public:
    Mapper105(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement, std::vector<uint8_t>* persistentMemory)
        :Mapper(prgBanks, chrBanks, initialArrangement)
    {
        control |= 0x0C;
        prgRam = persistentMemory;
    }

    bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) override 
    {
        if (addr >= 0x6000 && addr <= 0x7FFF && wRamEnabled)
        {
            // Read from PRG-RAM
            data = prgRam->at(addr & 0x1FFF);
            mappedAddr = DATA_UNMAPPED_BUT_SET;
            return true;
        }

        if (addr >= 0x8000)
        {
            if ((timer_prgRomConfig & 0x08) == 0)
            {
                mappedAddr = ((((timer_prgRomConfig >> 1) & 0x03) << 15) | (addr & 0x7FFF));
            }
            else if ((control & 0x08) == 0)
            {
                // Use second bank
                mappedAddr = 0x20000 | (((prgBank >> 1) << 15) | (addr & 0x7FFF));
            }
            else if ((control & 0x04) == 0)
            {
                // Use second bank
                if (addr >= 0x8000 && addr <= 0xBFFF)
                {
                    mappedAddr = 0x20000 | (addr & 0x3FFF);
                }
                else
                {
                    mappedAddr = 0x20000 | (((prgBank & 0x0F) << 14) | (addr & 0x3FFF));
                }
            }
            else
            {
                if (addr >= 0x8000 && addr <= 0xBFFF)
                {
                    mappedAddr = 0x20000 | (((prgBank & 0x0F) << 14) | (addr & 0x3FFF));
                }
                else
                {
                    mappedAddr = 0x20000 | ((7 << 14) | (addr & 0x3FFF));
                }
            }

            return true;
        }
        return false;
    }
    bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr >= 0x6000 && addr <= 0x7FFF && wRamEnabled)
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
                            control = (internalShiftRegister & 0x1F);
                            arrangement = controlMapArrangements[control & 0x03];
                            arrangementUpdated = true;
                            break;
                        // CHR0
                        case 1:
                            timer_prgRomConfig = (internalShiftRegister & 0x1F);

                            if ((internalShiftRegister & 0x10) == 0)
                            {
                                // timerIRQ = true;
                                unlockReq1 = true;
                                timerDisabled = false;
                            }
                            else
                            {
                                timerIRQ = false;
                                timerDisabled = true;
                                timer = 0;
                            }

                            if (unlockReq1 && ((internalShiftRegister & 0x10) == 1))
                                unlocked = true;

                            break;
                        // CHR1
                        case 2:
                            // Unused on NES-EVENT
                            break;
                        // PRG
                        case 3:
                            prgBank = (internalShiftRegister & 0x0F);
                            wRamEnabled = ((internalShiftRegister & 0x10) == 0);
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
        if (addr <= 0x1FFF)
        {
            mappedAddr = addr;
            return true;
        }
        return false;
    }
    bool chrBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) override
    {
        if (addr <= 0x1FFF)
        {
            mappedAddr = addr;
            return true;
        }
        return false;
    }

    bool checkIRQ() override
    {
        return timerIRQ;
    }

    void receiveExternalEvent(uint8_t ev) override
    {
        if (ev == EVENT_CPU_CLOCKED)
        {
            if (timerDisabled)
                timer = 0;
            else
            {
                timer++;

                // TODO: implement dip switches
                if (timer >= 0x20000000)
                {
                    printf("time!\n");
                    timerIRQ = true;
                    timerDisabled = true;
                }
            }
        }
    }

    void resetIRQ() override
    {
        timerIRQ = false;
    }

    std::string getMapperName() override
    {
        return "NES-EVENT";
    }

    uint32_t timer = 0;
private:
    std::vector<uint8_t>* prgRam;

    uint8_t internalShiftRegister = 0;
    uint8_t srWriteCount = 0;

    uint8_t control = 0;
    uint8_t timer_prgRomConfig = 0;
    uint8_t prgBank = 0;


    bool timerIRQ = false;
    bool timerDisabled = false;

    bool unlockReq1 = false;
    bool unlocked = false;

    bool wRamEnabled = true;

    Arrangement controlMapArrangements[4] =
    {
        ONE_SCREEN_A,
        ONE_SCREEN_B,
        HORIZONTAL,
        VERTICAL
    };
};