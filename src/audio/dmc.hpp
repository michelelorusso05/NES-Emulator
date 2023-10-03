#include <cstdint>
#include "channel.hpp"

class SampleChannel : public Channel
{
public:
    SampleChannel()
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