#pragma once

#include <cstdint>

#define DATA_UNMAPPED_BUT_SET   0xFFFFFFFF

#define EVENT_A12_CLOCKED       0x00
#define EVENT_CPU_CLOCKED       0x01

class Mapper {
public:

    enum Arrangement
    {
        VERTICAL,
        HORIZONTAL,
        ONE_SCREEN_A,
        ONE_SCREEN_B,
        FOUR_SCREENS
    };

    Mapper(uint8_t prgBanks, uint8_t chrBanks, Arrangement initialArrangement)
    {
        pBanks = prgBanks;
        cBanks = chrBanks;

        arrangement = initialArrangement;
    }

    // These functions return whether the mapper has intercepted the bus read/write
    virtual bool prgBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) = 0;
    virtual bool prgBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) = 0;
    virtual bool chrBankRead(uint16_t addr, uint32_t& mappedAddr, uint8_t& data) = 0;
    virtual bool chrBankWrite(uint16_t addr, uint32_t& mappedAddr, uint8_t data) = 0;

    virtual std::string getMapperName() = 0;

    Arrangement getArrangement()
    {
        return arrangement;
    }

    bool ArrangementUpdatedRequired()
    {
        bool a = arrangementUpdated;
        arrangementUpdated = false;
        return a;
    }
    virtual std::array<uint8_t, 1024>* GetAdditionalWindowRam(uint8_t window)
    {
        return nullptr;
    }

    virtual bool checkIRQ()
    {
        return false;
    }
    virtual void resetIRQ()
    {

    }
    virtual void scanlineCallback()
    {
        
    }
    virtual void reset()
    {

    }
    virtual void receiveExternalEvent(uint8_t ev)
    {

    }

protected:
    uint8_t pBanks;
    uint8_t cBanks;

    Arrangement arrangement;
    bool arrangementUpdated = false;
};