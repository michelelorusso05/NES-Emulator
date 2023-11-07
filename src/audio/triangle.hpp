#include <cstdint>
#include "channel.hpp"

static constexpr uint8_t triangleLookup[32] = 
{
    15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
};

class TriangleChannel : public Channel
{
public:
    TriangleChannel()
        :Channel()
    {

    }

    void Clock() override
    {
        sequencerTimer--;
        if (sequencerTimer == 0)
        {
            sequencerTimer = sequencerReload + 1;

            if (lengthCounter > 0 && linearCounterTimer > 0)
                lookupTablePointer = ((lookupTablePointer + 1) & 0x1F);
        }
    }
    void ClockLengthCounter()
    {
        if (!enabled)
            lengthCounter = 0;
        else
        {
            if (lengthCounter > 0 && !lengthCounterHalt)
                lengthCounter--;
        }
    }
    void ClockLinearCounter()
    {
        if (linearCounterReload)
        {
            linearCounterTimer = linearCounterReloadValue;
        }
        else if (linearCounterTimer > 0)
        {
            linearCounterTimer--;
        }

        if (!linearCounterControl)
        {
            linearCounterReload = false;
        }
    }
    uint8_t GetOutput()
    {
        return ComputeOutput();
    }
    uint8_t ComputeOutput()
    {
        if (sequencerReload <= 2)
            return 0;
        return triangleLookup[lookupTablePointer & 0x1F];
    }

    bool active()
    {
        return enabled && lengthCounter > 0 && linearCounterTimer > 0;
    }

    virtual void Reset() override
    {
        linearCounterControl = false;
        lengthCounterHalt = false;
        linearCounterReloadValue = 0;
        sequencerReload = 0;
        sequencerTimer = 0;
        lengthCounter = 0;
        linearCounterReload = false;

        output = 0;

        enabled = false;
    }

    bool linearCounterControl = false;
    bool lengthCounterHalt = false;
    uint8_t linearCounterReloadValue = 0;
    uint8_t linearCounterTimer = 0;

    uint16_t sequencerReload = 0;
    uint16_t sequencerTimer = 0;

    uint16_t lengthCounter = 0;
    bool linearCounterReload = false;

private:
    uint8_t output = 0;
    uint8_t lookupTablePointer = 0;
};