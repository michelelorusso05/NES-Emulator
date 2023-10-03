#pragma once

struct ButtonTexture
{
    int width;
    int height;
    int format;

    unsigned char* normalState;
    unsigned char* pressedState;

    int size;

    ButtonTexture(int w, int h, int f, unsigned char* nS, unsigned char* pS)
    {
        width = w;
        height = h;
        format = f;
        normalState = nS;
        pressedState = pS;

        size = w * h * 4;
    }
};