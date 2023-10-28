#include <cstdint>
#include "channel.hpp"
#include <iostream>

class PulseChannel : public Channel
{
public:
    PulseChannel(bool second)
        :Channel()
    {
        secondUnit = second;
    }

    void Clock() override
    {
        SweepUpdatePeriod();

        sequencerTimer--;
        if (sequencerTimer == 0)
        {
            sequencerTimer = ((sequencerReload + 1) << 1);
            sequencerCounter = ((sequencerCounter + 1) & 0x07);
        }
    }
    void ClockLengthCounter()
    {
        lengthClocked = true;

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
    void ClockSweep()
    {
        SweepUpdatePeriod();

		if (reloadSweep)
		{
			if (sweepEnabled && sweepDivider == 0)
			{
				if (sweepEnabled && sweepShift > 0 && !silenced)
                {
                    sequencerReload = sweepTarget;
                }
			}

            sweepDivider = sweepPeriodReload + 1;
            reloadSweep = false;
		}
		else
		{
			if (sweepDivider > 0)
			{
                sweepDivider--;
            }
			else if (sweepEnabled && sweepDivider == 0)
			{
				if (sweepEnabled && sweepShift > 0 && !silenced)
                {
                    sequencerReload = sweepTarget;
                }

                sweepDivider = sweepPeriodReload + 1;
			}

		}
    }
    void SweepUpdatePeriod()
    {
        sweepChangeAmount = (sequencerReload >> sweepShift);
        if (sweepNegate)
        {
            sweepTarget = sequencerReload - sweepChangeAmount;
            if (!secondUnit)
                sweepTarget--;
        }
        else
            sweepTarget = sequencerReload + sweepChangeAmount;

        
        silenced = ((sequencerReload < 8) || (!sweepNegate && (sweepTarget > 0x07FF)));
    }
    uint8_t GetOutput() override
    {
        return CalculateOutput();
    }

    uint8_t CalculateOutput()
    {
        SweepUpdatePeriod();
        if (enabled && !silenced && lengthCounter > 0)
        {
            if ((dutyCycles[dutyCycleSelect] >> (sequencerCounter & 0x07)) & 0x01)
            {
                if (constantVolume)
                    return volume_envelopeReload;
                else
                    return (envelopeDecay & 0x0F);
            }
        }
        return 0;
    }
    
    void SetPeriod(uint16_t period)
    {
        sequencerReload = (period & 0x07FF);
    }

    // Registers
    uint8_t dutyCycleSelect = 0;
    bool lengthCounterHalt = false;
    bool envelopeLoop = false;
    // Ignore envelope output
    bool constantVolume = false;
    uint8_t volume_envelopeReload = 0;

    bool sweepEnabled = false;
    uint8_t sweepPeriodReload = 0;
    bool sweepNegate = false;
    uint8_t sweepShift = 0;

    uint8_t lengthCounter = 0;

    bool reloadSweep = false;
    bool envelopeStart = false;
    uint16_t sequencerReload = 0;

    uint16_t sweepTarget = 0;
    uint16_t sequencerTimer = 0;

    bool lengthClocked = false;

    virtual void Reset() override
    {
        dutyCycleSelect = 0;
        lengthCounterHalt = false;
        envelopeLoop = false;
        constantVolume = false;
        volume_envelopeReload = 0;
        sweepEnabled = false;
        sweepPeriodReload = 0;
        sweepNegate = false;
        sweepShift = 0;
        lengthCounter = 0;
        reloadSweep = false;
        envelopeStart = false;
        sequencerReload = 0;
        sweepTarget = 0;
        sequencerTimer = 0;

        sweepDivider = 0;
        sweepChangeAmount = 0;
        reloadLengthCounter = false;
        envelopeDecay = 0;
        envelopeDivider = 0;
        sequencerCounter = 0;
        output = 0;

        silenced = false;

        enabled = false;
    }

    uint8_t sequencerCounter = 0;
private:
    bool secondUnit;

    uint8_t sweepDivider = 0;
    uint16_t sweepChangeAmount = 0;

    bool reloadLengthCounter = false;
    uint8_t envelopeDecay = 0;
    uint8_t envelopeDivider = 0;


    uint8_t output = 0;

    uint8_t dutyCycles[4] = 
    {
        // 12.5%
        0b01000000,
        // 25%
        0b01100000,
        // 50%
        0b01111000,
        // NOT 25%
        0b10011111
    };
};