#pragma once

#include <cstdint>
#include <array>
#include "../include/raylib.h"

#include "cartridge.hpp"

class Bus;

class PPU
{
public:
    PPU(Bus* master);
    ~PPU();

    bool clock();
    void reset();

    void writeRegisters(uint8_t tRegister, uint8_t value);
    uint8_t readRegisters(uint8_t tRegister);

    // Read/Write from/to PPU bus
    void writePPU(uint16_t addr, uint8_t value);
    uint8_t readPPU(uint16_t addr);

    uint8_t* GetScreen()
    {
        return screen;
    }

    void SetPixel(uint8_t x, uint8_t y, uint32_t color);
    uint32_t GetColorForPixel(uint8_t pix, uint8_t paletteIndex);
    uint32_t GetColorForPixelForceGrayScale(uint8_t pix, uint8_t paletteIndex);

    // Debug functions
    void drawPatternTable(int x, int y, int bankNo);
    void drawOAM(int x, int y);
    void drawSecondaryOAM(int x, int y);
    void drawPalette(int x, int y, int paletteNo);
    Color getColorFromPaletteAddress(uint8_t off);

    void LoadCartridge(Cartridge *cart)
    {
        cartridge = cart;
        SetArrangement(cart->GetArrangement());
    }
    void UnloadCartridge()
    {
        cartridge = nullptr;
    }

    bool checkNMI()
    {
        bool nmi = (((status & 0x80) & (control & 0x80)) > 0);
        return nmi;
    }
    // Register 0x2000
    uint8_t control;

    // Register 0x2001
    uint8_t ppumask;
    
    // Register 0x2002
    uint8_t status;

    // Register 0x2003
    uint8_t oamAddr;

    // Register 0x2004
    uint8_t oamData;
private:
    /*
        Sets the window arrangement.

        ┌───────────┬───────────┐
        │ 0x2000    │    0x2400 │
        │     A     │     B     │
        │           │           │
        ├───────────┼───────────┤
        │           │           │
        │     C     │     D     │
        │ 0x2800    │    0x2C00 │
        └───────────┴───────────┘

    */
    void SetArrangement(Mapper::Arrangement arr);

    Cartridge* cartridge = nullptr;

    bool vBlank = false;
    int16_t scanline = -1;
    int16_t pixel = 0;
    uint64_t frame = 0;
    bool oddFrame = false;
    bool suppressVblankSetting = false;

    uint32_t palette[64];

    uint8_t* screen;

    Bus* bus = nullptr;

    std::array<uint8_t, 1024> vRamBank0;
    std::array<uint8_t, 1024> vRamBank1;

    std::array<uint8_t, 1024>* windows[4];

    std::array<uint8_t, 32> paletteRam;

    // False: low, True: high
    bool addressWriteLatch = false;
    uint8_t dataBuf = 0;

    // Background rendering registers

    uint16_t v;
    uint16_t t;

    uint8_t fineXScroll = 0;

    uint8_t nextTileID = 0x00;
    uint8_t nextTileAttr = 0x00;
    uint8_t nextTileLSB = 0x00;
    uint8_t nextTileMSB = 0x00;

    uint16_t shiftRegisterPatternLower = 0x0000;
    uint16_t shiftRegisterPatternHigher = 0x0000;
    uint16_t shiftRegisterAttributeLower = 0x0000;
    uint16_t shiftRegisterAttributeHigher = 0x0000;

    // Sprite rendering registers and memory
    std::array<uint8_t, 256> oam;
    std::array<uint8_t, 32> secondaryOam;

    uint8_t n = 0;
    uint8_t found = 0;

    bool zeroStored = false;
    bool zeroRendered = false;

    struct SpriteSystem {
        uint8_t lsbShiftRegister;
        uint8_t msbShiftRegister;

        uint8_t attr;

        uint8_t xPosCounter;

        bool active;
        bool drawn;

        uint8_t originalOAMid;
    };

    SpriteSystem sprites[8];

    bool nmiOccurred = false;
    bool nmiSuppressed = false;

    // Clock helper functions
    void IncHorz();
    void IncVert();
    void TransferHorz();
    void TransferVert();
    void LoadShiftRegisters();
    void UpdateShiftRegisters();
};