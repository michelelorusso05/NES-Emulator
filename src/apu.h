#pragma once

#include <cstdint>
#include "../include/raylib.h"

#include "audio/pulse.hpp"
#include "audio/triangle.hpp"
#include "audio/noise.hpp"
#include "audio/dmc.hpp"

class APU
{
public:
    APU();
    ~APU();

    void clock();
    void writeRegisters(uint8_t reg, uint8_t value);
    uint8_t readRegisters(uint8_t reg);

    double getOutput();

    void reset();

    bool irq = false;

private:
    PulseChannel squareChannel1 = PulseChannel(false);
    PulseChannel squareChannel2 = PulseChannel(true);
    TriangleChannel triangleChannel;
    NoiseChannel noiseChannel;
    SampleChannel sampleChannel;

    uint8_t control = 0;
    uint8_t status = 0;
    uint8_t modeAndInterrupt = 0;

    uint32_t clockCounter = 0;
    uint32_t frameClockCounter = 0;
};