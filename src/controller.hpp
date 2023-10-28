#include <cstdint>
#include <iostream>

class Controller
{
public:
    enum Buttons
    {
        A = 0x01 << 0,
        B = 0x01 << 1,
        Select = 0x01 << 2,
        Start = 0x01 << 3,
        Up = 0x01 << 4,
        Down = 0x01 << 5,
        Left = 0x01 << 6,
        Right = 0x01 << 7
    };

    Controller()
    {

    }

    uint8_t data = 0;
    uint8_t latch = 0;

    uint8_t Read()
    {
        uint8_t d = (data & 0x01);
        data >>= 1;

        return d;
    }
    void SetButton(Buttons button, bool set)
    {
        if (set)
        {
            latch |= button;
        }
        else
            latch &= ~button;
    }
    void Transfer()
    {
        data = latch;
    }
};