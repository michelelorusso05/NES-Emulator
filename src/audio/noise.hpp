#include <cstdint>
#include "channel.hpp"

static constexpr uint16_t timerReloadTable[] = {
        4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068
};

class NoiseChannel : public Channel
{
public:
    NoiseChannel()
        :Channel()
    {
        Reset();
        envelopeLoop = true;
    }

    void Clock() override
    {
        timer--;
        if (timer == 0)
        {
            timer = ((timerReload + 1) << 1);

            feedback = (((linearFeedbackRegister & 0x01) > 0) ^ ((linearFeedbackRegister & (mode ? 0x40 : 0x02)) > 0));
            linearFeedbackRegister >>= 1;
            linearFeedbackRegister |= (((uint16_t) feedback) << 14);
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
    void ClockEnvelope()
    {
        if (envelopeStart)
        {
            envelopeStart = false;
            envelopeDecay = 15;
            envelopeDivider = volume_envelopeReload;
        }
        else
        {
            if (envelopeDivider == 0)
            {
                envelopeDivider = volume_envelopeReload;

                if (envelopeDecay > 0)
                    envelopeDecay--;
                else
                {
                    if (envelopeLoop)
                        envelopeDecay = 15;
                }
            }
            else
                envelopeDivider--;
        }
    }

    void LoadPeriod(uint8_t index)
    {
        timerReload = timerReloadTable[index];
    }

    uint8_t GetOutput() override
    {
        return CalculateOutput();
    }

    uint8_t CalculateOutput()
    {
        if (enabled && !silenced && lengthCounter > 0)
        {
            if ((linearFeedbackRegister & 0x01) == 0)
            {
                if (constantVolume)
                    return volume_envelopeReload;
                else
                    return (envelopeDecay & 0x0F);
            }
        }
        return 0;
    }

    
    // Registers
    bool lengthCounterHalt = false;
    bool envelopeLoop = false;
    // Ignore envelope output
    bool constantVolume = false;
    uint8_t volume_envelopeReload = 0;

    uint8_t lengthCounter = 0;

    bool envelopeStart = false;
    bool mode = false;

    virtual void Reset() override
    {
        lengthCounterHalt = false;
        envelopeLoop = false;
        constantVolume = false;
        volume_envelopeReload = 0;
        lengthCounter = 0;
        envelopeStart = false;
        reloadLengthCounter = false;
        envelopeDecay = 0;
        envelopeDivider = 0;
        mode = false;
        feedback = false;

        silenced = false;

        enabled = false;

        linearFeedbackRegister = 1;
    }
private:
    bool reloadLengthCounter = false;
    uint8_t envelopeDecay = 0;
    uint8_t envelopeDivider = 0;
    uint16_t timer = 0;
    uint16_t timerReload = 0;

    uint16_t linearFeedbackRegister = 0;
    bool feedback = true;
};