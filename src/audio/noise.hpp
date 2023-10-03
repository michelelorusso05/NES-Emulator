#include <cstdint>
#include "channel.hpp"

class NoiseChannel : public Channel
{
public:
    NoiseChannel()
        :Channel()
    {

    }

    void Clock() override
    {

    }
    uint8_t GetOutput() override
    {
        return 0;
    }
};