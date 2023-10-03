#pragma once

#include <cstdint>

class Channel
{
public:
    Channel()
    {

    }

    virtual void Clock() = 0;
    virtual uint8_t GetOutput() = 0;

    bool enabled = false;
    bool silenced = false;

    uint8_t requestedValues[4];
    bool latches[4] = { false };

    virtual void Reset()
    {
        
    }

protected:
    uint8_t lengthCounterLoadTable[32] = 
    {
         10, 254,  20,   2,  40,   4,  80,   6, 160,   8,  60,  10,  14,  12,  26,  14,
         12,  16,  24,  18,  48,  20,  96,  22, 192,  24,  72,  26,  16,  28,  32,  30
    };
};