#include "ppu.h"
#include "bus.hpp"

// General sizes and offsets
#define CHR_ROM_BANK_OFFSET     0x1000
#define PALETTE_RAM_OFFSET      0x3F00
#define NAMETABLE_OFFSET        0x2000
#define NAMETABLE_SIZE          0x0400

// Register 0x2000 CONTROL
#define CONTROL_NAMETABLE_X     0x01
#define CONTROL_NAMETABLE_Y     0x02
#define CONTROL_NAMETABLES      0x03
#define CONTROL_VRAM_INCREMENT  0x04
#define CONTROL_SPRITE_TABLE    0x08
#define CONTROL_BG_TABLE        0x10
#define CONTROL_SPRITE_SIZE     0x20
#define CONTROL_SLAVE_SELECT    0x40
#define CONTROL_GENERATE_NMI    0x80

// REGISTER 0x2001 PPUMASK
#define MASK_GREYSCALE          0x01
#define MASK_SHOW_LEFT_BG       0x02
#define MASK_SHOW_LEFT_SPRITES  0x04
#define MASK_SHOW_BACKGROUND    0x08
#define MASK_SHOW_SPRITES       0x10
#define MASK_RENDERING          0x18
#define MASK_EMP_RED            0x20
#define MASK_EMP_GREEN          0x40
#define MASK_EMP_BLUE           0x80

// REGISTER 0x2002 STATUS
#define STATUS_SPRITE_OVERFLOW  0x20
#define STATUS_SPRITE_ZERO_HIT  0x40
#define STATUS_VBLANK           0x80

// Speed is key
static uint8_t reverseBitLookup[] = {
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
    0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
    0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
    0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
    0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
    0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 
    0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
    0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 
    0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
    0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 
    0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

#define reverse(a) reverseBitLookup[a]

PPU::PPU(Bus* master)
{
    bus = master;

    screenBuf0 = new uint8_t[256 * 240 * 3];
    screenBuf1 = new uint8_t[256 * 240 * 3];

    screen = screenBuf0;
    bufferedScreen = screenBuf1;

    palette[0x00] = 0x626262FF;
    palette[0x01] = 0x001FB2FF;
    palette[0x02] = 0x2404C8FF;
    palette[0x03] = 0x5200B2FF;
    palette[0x04] = 0x730076FF;
    palette[0x05] = 0x800024FF;
    palette[0x06] = 0x730B00FF;
    palette[0x07] = 0x522800FF;
    palette[0x08] = 0x244400FF;
    palette[0x09] = 0x005700FF;
    palette[0x0A] = 0x005C00FF;
    palette[0x0B] = 0x005324FF;
    palette[0x0C] = 0x003C76FF;
    palette[0x0D] = 0x000000FF;
    palette[0x0E] = 0x000000FF;
    palette[0x0F] = 0x000000FF;

    palette[0x10] = 0xABABABFF;
    palette[0x11] = 0x0D57FFFF;
    palette[0x12] = 0x4B30FFFF;
    palette[0x13] = 0x8A13FFFF;
    palette[0x14] = 0xBC08D6FF;
    palette[0x15] = 0xD21269FF;
    palette[0x16] = 0xC72E00FF;
    palette[0x17] = 0x9D5400FF;
    palette[0x18] = 0x607B00FF;
    palette[0x19] = 0x209800FF;
    palette[0x1A] = 0x00A300FF;
    palette[0x1B] = 0x009942FF;
    palette[0x1C] = 0x007DB4FF;
    palette[0x1D] = 0x000000FF;
    palette[0x1E] = 0x000000FF;
    palette[0x1F] = 0x000000FF;

    palette[0x20] = 0xFFFFFFFF;
    palette[0x21] = 0x53AEFFFF;
    palette[0x22] = 0x9085FFFF;
    palette[0x23] = 0xD365FFFF;
    palette[0x24] = 0xFF57FFFF;
    palette[0x25] = 0xFF5DCFFF;
    palette[0x26] = 0xFF7757FF;
    palette[0x27] = 0xFA9E00FF;
    palette[0x28] = 0xBDC700FF;
    palette[0x29] = 0x7AE700FF;
    palette[0x2A] = 0x43F611FF;
    palette[0x2B] = 0x26EF7EFF;
    palette[0x2C] = 0x2CD5F6FF;
    palette[0x2D] = 0x4E4E4EFF;
    palette[0x2E] = 0x000000FF;
    palette[0x2F] = 0x000000FF;

    palette[0x30] = 0xFFFFFFFF;
    palette[0x31] = 0xB6E1FFFF;
    palette[0x32] = 0xCED1FFFF;
    palette[0x33] = 0xE9C3FFFF;
    palette[0x34] = 0xFFBCFFFF;
    palette[0x35] = 0xFFBDF4FF;
    palette[0x36] = 0xFFC6C3FF;
    palette[0x37] = 0xFFD59AFF;
    palette[0x38] = 0xE9E681FF;
    palette[0x39] = 0xCEF481FF;
    palette[0x3A] = 0xB6FB9AFF;
    palette[0x3B] = 0xA9FAC3FF;
    palette[0x3C] = 0xA9F0F4FF;
    palette[0x3D] = 0xB8B8B8FF;
    palette[0x3E] = 0x000000FF;
    palette[0x3F] = 0x000000FF;

    SetArrangement(Mapper::HORIZONTAL);

    reset();
}
PPU::~PPU()
{
    delete screenBuf0;
    delete screenBuf1;
}

// Screen is R8G8B8 format
void PPU::SetPixel(uint8_t x, uint8_t y, uint32_t color)
{
    uint32_t off = (x | (y << 8)) * 3;

    screen[off] = color >> 24;
    screen[off + 1] = color >> 16 & 0xFF;
    screen[off + 2] = color >> 8 & 0xFF;
}

uint32_t PPU::GetColorForPixel(uint8_t pix, uint8_t paletteIndex)
{
    // pixel mask 00 means transparency, so the universal background color must be returned
    return palette[readPPU(PALETTE_RAM_OFFSET | (pix ? ((paletteIndex << 2) | pix) : 0)) & 0x3F];
}

uint32_t PPU::GetColorForPixelForceGrayScale(uint8_t pix, uint8_t paletteIndex)
{
    return palette[readPPU(PALETTE_RAM_OFFSET | (pix ? ((paletteIndex << 2) | pix) : 0)) & 0x30];
}

// Draw a pattern table stored in CHR ROM
void PPU::drawPatternTable(int x, int y, int bankNo)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // Every tile takes up 16 bytes
            uint16_t offset = j * 16 + i * 256;

            for (int r = 0; r < 8; r++)
            {
                uint8_t lsb = readPPU(bankNo * CHR_ROM_BANK_OFFSET + offset + r + 0);
                uint8_t msb = readPPU(bankNo * CHR_ROM_BANK_OFFSET + offset + r + 8);

                for (int c = 0; c < 8; c++)
                {
                    uint8_t p = (lsb >> 7) | ((msb >> 7) << 1);

                    lsb <<= 1;
                    msb <<= 1;

                    // Draw greyscale bitmask
                    DrawRectangle(x + (j * 8 + c) * 2, y + (i * 8 + r) * 2, 2, 2, GetColor(((((0xFFFFFF / 3) * p) << 8) + 0xFF)));
                }
            }
        }
    }
}

void PPU::drawOAM(int x, int y)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Every sprite takes up 4 bytes
            uint16_t spriteAddr = j * 4 + i * 8 * 4;
            uint16_t offset = (control & CONTROL_SPRITE_TABLE > 0) * 0x1000 + oam.at(spriteAddr | 1) * 16;
            uint8_t paletteIndex = ((oam.at(spriteAddr | 2) & 0x03) | 4);
            bool reverseY = oam.at(spriteAddr | 2) & 0x80;
            bool reverseX = oam.at(spriteAddr | 2) & 0x40;

            bool active = oam.at(spriteAddr) < 0xEF;

            for (int r = 0; r < 8; r++)
            {
                uint8_t lsb = readPPU(offset + (reverseY ? (8 - r) : r) + 0);
                uint8_t msb = readPPU(offset + (reverseY ? (8 - r) : r) + 8);

                if (reverseX)
                {
                    lsb = reverse(lsb);
                    msb = reverse(msb);
                }

                for (int c = 0; c < 8; c++)
                {
                    uint8_t p = (lsb >> 7) | ((msb >> 7) << 1);

                    lsb <<= 1;
                    msb <<= 1;

                    DrawRectangle(x + (j * 8 + c) * 2, y + (i * 8 + r) * 2, 2, 2, 
                        GetColor(active ? GetColorForPixel(p, paletteIndex) : GetColorForPixelForceGrayScale(p, paletteIndex)));
                }
            }
        }
    }
}

void PPU::drawSecondaryOAM(int x, int y)
{
    for (int j = 0; j < 8; j++)
    {
        // Every sprite takes up 4 bytes
        uint16_t spriteAddr = j * 4;
        uint16_t offset = (control & CONTROL_SPRITE_TABLE > 0) * 0x1000 + secondaryOam.at(spriteAddr | 1) * 16;
        uint8_t paletteIndex = ((secondaryOam.at(spriteAddr | 2) & 0x03) | 4);
        bool reverseY = secondaryOam.at(spriteAddr | 2) & 0x80;
        bool reverseX = secondaryOam.at(spriteAddr | 2) & 0x40;

        for (int r = 0; r < 8; r++)
        {
            uint8_t lsb = readPPU(offset + (reverseY ? (8 - r) : r) + 0);
            uint8_t msb = readPPU(offset + (reverseY ? (8 - r) : r) + 8);

            if (reverseX)
            {
                lsb = reverse(lsb);
                msb = reverse(msb);
            }

            for (int c = 0; c < 8; c++)
            {
                uint8_t p = (lsb >> 7) | ((msb >> 7) << 1);

                lsb <<= 1;
                msb <<= 1;

                DrawRectangle(x + (j * 8 + c) * 2, y + r * 2, 2, 2, GetColor(GetColorForPixel(p, paletteIndex)));
            }
        }
    }
}

void PPU::drawPalette(int x, int y, int paletteNo)
{
    uint16_t offset = PALETTE_RAM_OFFSET | (paletteNo << 0x02);

    for (int i = 0; i < 4; i++)
    {
        DrawRectangle(x + 26 * i, y, 24, 24, GetColor(palette[readPPU(offset | i)]));
    }
}

Color PPU::getColorFromPaletteAddress(uint8_t off)
{
    return GetColor(palette[readPPU(PALETTE_RAM_OFFSET | off)]);
}

// Reference: https://www.nesdev.org/wiki/PPU_registers and https://www.nesdev.org/wiki/PPU_scrolling
void PPU::writeRegisters(uint8_t tRegister, uint8_t value)
{
    switch (tRegister)
    {
        case 0:
            // Rightmost two bits are used to select the nametable
            control = (value & (~CONTROL_NAMETABLES));

            // Loopy register bits 10 and 11 are reserved for nametables (0x0C00)
            t = (t & ~0x0C00) | (((uint16_t)value & CONTROL_NAMETABLES) << 10);
            break;
        case 1:
            ppumask = value;
            break;
        case 2:
            // Register 2 is read only
            break;
        case 3:
            oamAddr = value;
            break;
        case 4:
            oam.at(oamAddr) = value;
            oamAddr++;
            break;
        case 5:
            // Write to X scroll (both coarse and fine)
            if (!addressWriteLatch)
            {
                /*
                    t: ....... ...ABCDE <- d: ABCDE...
                    x:              FGH <- d: .....FGH
                    w:                  <- 1
                    where W is the addressWriteLatch
                */
                fineXScroll = value & 0x07;
                t = (t & ~0x1F) | (value >> 3);
                addressWriteLatch = true;
            }
            // Write to Y scroll (both coarse and fine)
            else
            {
                /*
                    t: FGH..AB CDE..... <- d: ABCDEFGH
                    w:                  <- 0
                */
                t = (t & ~0x73E0) | ((value & 0x07) << 12) | (((uint16_t)(value & 0xF8)) << 2);
                addressWriteLatch = false;
            }
            break;
        case 6:
            if (!addressWriteLatch)
            {
                /*
                    t: .CDEFGH ........ <- d: ..CDEFGH
                           <unused>     <- d: AB......
                    t: Z...... ........ <- 0 (bit Z is cleared)
                    w:                  <- 1
                */
                t = (uint16_t)((value & 0x3F) << 8) | (t & 0x00FF);
                addressWriteLatch = true;
            }
            else
            {
                /*
                    t: ....... ABCDEFGH <- d: ABCDEFGH
                    v: <...all bits...> <- t: <...all bits...>
                    w:                  <- 0
                */
                t = (t & 0xFF00) | value;
                v = t;
                addressWriteLatch = false;
            }
            break;
        case 7:
            writePPU(v, value);
            v += ((control & CONTROL_VRAM_INCREMENT) ? 32 : 1);
            break;

        // DMA
        case 0x14:
            uint16_t addr = (value << 8);

            for (int i = 0x00; i <= 0xFF; i++)
                writeRegisters(0x04, bus->read(addr | i));

            bus->cpu.cycles += (513 + (bus->cpu.cycles & 0x01));
            break;
    }
}

uint8_t PPU::readRegisters(uint8_t tRegister)
{
    switch (tRegister)
    {
        case 0:
            // Register 0 is write only
            break;
        case 1:
            // Register 1 is write only
            break;
        case 2:
        {
            // Unused bits on the status registers are mapped to the leftovers of the dataBuf latch
            uint8_t data = (status & 0xE0) | (dataBuf & 0x1F);
            // VBlank is always cleared on 0x2002 read
            status &= ~STATUS_VBLANK;
            if (scanline == 241 && pixel == 1)
            {
                suppressVblankSetting = true;
            }
            addressWriteLatch = false;
            return data;
            break;
        }
        case 3:
            // Register 3 is write only
            break;
        case 4:
            return oam.at(oamAddr);
            break;
        case 5:
            // Register 5 is write only
            break;
        case 6:
            // Register 6 is write only
            break;
        case 7:
        {
            uint8_t data = dataBuf;
            dataBuf = readPPU(v);
            
            // Palettes are not buffered
            if (v >= PALETTE_RAM_OFFSET)
            {
                data = dataBuf;

                // When reading palette ram, the buffer is loaded with mirrored nametable ram normally shadowed by palette ram
                dataBuf = readPPU(v & ~0x1000);
            }

            v += ((control & CONTROL_VRAM_INCREMENT) ? 32 : 1);
            
            return data;
            break;
        }
        // DMA
        case 0x14:
            // DMA is write only
            break;
    }

    // Sort of open bus
    return dataBuf;
}

void PPU::writePPU(uint16_t addr, uint8_t value)
{
    addr &= 0x3FFF;

    // Cartridge cannot reroute addresses from 0x3F00 to 0x3FFF
    if (addr >= 0x3F00 && addr <= 0x3FFF)
    {
        addr &= 0x001F;

        if (addr == 0x0010)
            addr = 0x0000;
        if (addr == 0x0014)
            addr = 0x0004;
        if (addr == 0x0018)
            addr = 0x0008;
        if (addr == 0x001C)
            addr = 0x000C;

        paletteRam.at(addr) = value;

        return;
    }
    
    if (cartridge != nullptr && cartridge->ppuWrite(addr, value))
        return;

    if (addr >= 0x2000 && addr <= 0x3EFF)
    {
        if (cartridge != nullptr && cartridge->ArrangementUpdateRequired())
            SetArrangement(cartridge->GetArrangement());
        uint8_t bank = ((addr >> 10) & 0b00000011);
        windows[bank]->at(addr & 0x03FF) = value;
    }
}

uint8_t PPU::readPPU(uint16_t addr)
{
    addr &= 0x3FFF;

    // Cartridge cannot reroute addresses from 0x3F00 to 0x3FFF
    if (addr >= 0x3F00 && addr <= 0x3FFF)
    {
        addr &= 0x001F;

        if (addr == 0x0010)
            addr = 0x0000;
        if (addr == 0x0014)
            addr = 0x0004;
        if (addr == 0x0018)
            addr = 0x0008;
        if (addr == 0x001C)
            addr = 0x000C;

        return paletteRam.at(addr) & ((ppumask & MASK_GREYSCALE) ? 0x30 : 0x3F);
    }

    uint8_t data;
    if (cartridge != nullptr && cartridge->ppuRead(addr, data))
        return data;
    
    if (addr >= 0x2000 && addr <= 0x3EFF)
    {
        if (cartridge != nullptr && cartridge->ArrangementUpdateRequired())
            SetArrangement(cartridge->GetArrangement());
        uint8_t bank = ((addr >> 10) & 0b00000011);
        return windows[bank]->at(addr & 0x03FF);
    }
    
    return 0;
}

// Clock helper functions
void PPU::IncHorz()
{
    // Return if rendering is disabled
    if ((ppumask & (MASK_SHOW_BACKGROUND | MASK_SHOW_SPRITES)) == 0)
        return;

    if ((v & 0x1F) == 31)
    {
        v &= ~0x001F;
        v ^= 0x0400;
    }
    else
        v++;
}
void PPU::IncVert()
{
    // Return if rendering is disabled
    if ((ppumask & (MASK_SHOW_BACKGROUND | MASK_SHOW_SPRITES)) == 0)
        return;

    if ((v & 0x7000) != 0x7000)
        v += 0x1000;
    else
    {
        v &= ~0x7000;
        uint16_t y = (v & 0x03E0) >> 5;
        if (y == 29)
        {
            y = 0;
            v ^= 0x0800;
        }
        else if (y == 31)
            y = 0;
        else
            y += 1;
            
        v = (v & ~0x03E0) | ((uint16_t)y << 5);
    }
}
void PPU::TransferHorz()
{
    // Return if rendering is disabled
    if ((ppumask & (MASK_SHOW_BACKGROUND | MASK_SHOW_SPRITES)) == 0)
        return;

    // Copy over nametable X and coarse X
    v = (v & ~0x041F) | (t & 0x041F);
}
void PPU::TransferVert()
{
    // Return if rendering is disabled
    if ((ppumask & (MASK_SHOW_BACKGROUND | MASK_SHOW_SPRITES)) == 0)
        return;

    // Copy over nametable Y, coarse Y and fine Y
    v = (v & ~0x7BE0) | (t & 0x7BE0);
}
void PPU::LoadShiftRegisters()
{
    shiftRegisterPatternLower = (shiftRegisterPatternLower & 0xFF00) | nextTileLSB;
    shiftRegisterPatternHigher = (shiftRegisterPatternHigher & 0xFF00) | nextTileMSB;

    shiftRegisterAttributeLower = (shiftRegisterAttributeLower & 0xFF00) | ((nextTileAttr & 0b01) ? 0xFF : 0x00);
    shiftRegisterAttributeHigher = (shiftRegisterAttributeHigher & 0xFF00) | ((nextTileAttr & 0b10) ? 0xFF : 0x00);
}
void PPU::UpdateShiftRegisters()
{
    if ((ppumask & MASK_SHOW_BACKGROUND) != 0)
    {
        shiftRegisterPatternLower <<= 1;
        shiftRegisterPatternHigher <<= 1;
        shiftRegisterAttributeLower <<= 1;
        shiftRegisterAttributeHigher <<= 1;
    }
    if ((ppumask & MASK_SHOW_SPRITES) != 0 && pixel >= 1 && pixel <= 257)
    {
        for (uint8_t i = 0; i < found; i++)
        {
            if (sprites[i].xPosCounter > 0)
                sprites[i].xPosCounter--;

            else
            {
                sprites[i].lsbShiftRegister <<= 1;
                sprites[i].msbShiftRegister <<= 1;
            }
        }
    }
}

// Reference: https://www.nesdev.org/w/images/default/4/4f/Ppu.svg
void PPU::clock()
{
    // Visible scanlines
    if (scanline >= -1 && scanline <= 239)
    {
        // Miscellaneous

        // Prerender scanline
        if (scanline == -1)
        {
            if (pixel == 1)
            {
                // Clear vBlank, Zero hit and Sprite overflow flags
                status &= ~(STATUS_VBLANK | STATUS_SPRITE_ZERO_HIT | STATUS_SPRITE_OVERFLOW);
                vBlank = false;
                nmiSuppressed = false;
            }
            
            // Odd-frame skip
            if ((ppumask & (MASK_SHOW_BACKGROUND | MASK_SHOW_SPRITES)))
            {
                if (pixel == 339 && oddFrame)
                {
                    pixel = 340;
                }
            }
        }

        // Background
        if ((pixel >= 2 && pixel <= 257) || (pixel >= 321 && pixel <= 337))
        {
            UpdateShiftRegisters();

            switch ((pixel - 1) & 0x07)
            {
                case 0:
                    LoadShiftRegisters();
                    // Fetch nametable bytes
                    nextTileID = readPPU(0x2000 | (v & 0x0FFF));
                    break;
                case 2:
                    // Fetch attribute table bytes
                    nextTileAttr = readPPU(0x23C0 | (v & 0x0C00) |
                                           (((v & 0x3E0) >> 7) << 3) | ((v & 0x1F) >> 2));
                    
                    if ((v >> 5) & 0x02)
                        nextTileAttr >>= 4;
                    if (v & 0x02)
                        nextTileAttr >>= 2;
                    nextTileAttr &= 0x03;
                    break;
                case 4:
                {
                    // Fetch background lower 8 bits
                    uint16_t adr = ((uint16_t) (control & 0x10) << 8) + (((uint16_t)nextTileID) << 4) + ((v >> 12) & 0x07);
                    nextTileLSB = readPPU(adr);
                    break;
                }
                case 6:
                    // Fetch background higher 8 bits
                    nextTileMSB = readPPU(((uint16_t) (control & 0x10) << 8) + (((uint16_t) nextTileID) << 4) + ((v >> 12) & 0x07) + 8);
                    break;
                case 7:
                    // Increase horizontal scroll
                    IncHorz();
                    break;
            }
        }
        if (pixel == 256)
        {
            IncVert();
        }
        else if (pixel == 257)
        {
            LoadShiftRegisters();
            TransferHorz();
        }

        else if (pixel == 338 || pixel == 340)
		{
			nextTileID = readPPU(0x2000 | (v & 0x0FFF));
		}

        if (scanline == -1 && pixel >= 280 && pixel <= 304)
            TransferVert();

        // Sprites
        if (scanline >= 0 && scanline <= 239)
        {
            // Clear secondary OAM
            if (pixel == 1)
                secondaryOam.fill(0);

            // Sprite evaluation

            // TODO: Rewrite to be cycle accurate to pass #3 - Timing (and possibly #4 - Obscure)
            if (pixel == 257)
            {
                found = 0;
                n = 0;
                // Keep n between 0 and 63
                while (found <= 7)
                {
                    /*
                    if (found == 8)
                    {
                        if (ppumask & MASK_RENDERING)
                            status |= STATUS_SPRITE_OVERFLOW;
                        break;
                    }
                    */

                    uint8_t fetchedY = oam.at(n);

                    int16_t diff = (int16_t) scanline - (int16_t) fetchedY;

                    secondaryOam.at(found << 2) = fetchedY;

                    if (diff >= 0 && diff < (control & CONTROL_SPRITE_SIZE ? 16 : 8))
                    {
                        for (uint8_t i = 1; i < 4; i++)
                            secondaryOam.at((found << 2) | i) = oam.at(n | i);

                        found++;

                        if (n == 0)
                            zeroStored = true;
                    }
                    else
                    {
                        if (n == 0)
                            zeroStored = false;
                    }

                    n += 4;

                    if (n == 0)
                    {
                        break;
                    }
                }

                uint16_t m = 0;
                uint8_t oldN = n;
                while (n != 0)
                {
                    uint8_t fetchedY = oam.at((n + m) & 0xFF);
                    m = ((m + 1) & 4);
                    int16_t diff = (int16_t) scanline - (int16_t) fetchedY;

                    if (diff >= 0 && diff < (control & CONTROL_SPRITE_SIZE ? 16 : 8))
                    {
                        if (ppumask & MASK_RENDERING)
                            status |= STATUS_SPRITE_OVERFLOW;

                        // PPU reads next 3 bytes from OAM. Because of the hardware bug (below), m might not be 1 here, so
                        // we carefully increment n when m overflows.
                        for (int i = 0; i < 3; ++i)
                        {
                            m++;
                            if (m >= 4)
                            {
                                m -= 4;
                                n += 4;
                            }

                        }
                    }
                    else
                    {
                        n += 4;
                        
                        m = ((m + 1) & 4);
                    }
                }
            }

            // Sprite circuits population
            if (pixel == 340)
            {
                for (uint8_t i = 0; i < found; i++)
                {
                    // 8x8 mode
                    if ((control & CONTROL_SPRITE_SIZE) == 0)
                    {
                        bool inverseY = (secondaryOam.at((i << 2) | 2) & 0x80);
                        uint8_t tileRow = (scanline - secondaryOam.at(i << 2));
                        uint16_t offset = ((control & 0x08) << 9) | (secondaryOam.at((i << 2) | 1) << 4) + (inverseY ? (7 - tileRow) : tileRow);
                        sprites[i].lsbShiftRegister = readPPU(offset + 0);
                        sprites[i].msbShiftRegister = readPPU(offset + 8);

                        sprites[i].attr = secondaryOam.at((i << 2) | 2);

                        if ((sprites[i].attr & 0x40))
                        {
                            sprites[i].lsbShiftRegister = reverseBitLookup[sprites[i].lsbShiftRegister];
                            sprites[i].msbShiftRegister = reverseBitLookup[sprites[i].msbShiftRegister];
                        }

                        sprites[i].xPosCounter = secondaryOam.at((i << 2) | 3);

                        sprites[i].active = false;
                        sprites[i].drawn = (i < found);
                    }
                    // 8x16 mode
                    else
                    {
                        bool inverseY = (secondaryOam.at((i << 2) | 2) & 0x80);
                        uint8_t tileRow = (scanline - secondaryOam.at(i << 2));
                        uint16_t offset;

                        uint16_t bankSelect = ((secondaryOam.at((i << 2) | 1)) & 0x01) << 12;

                        if (inverseY)
                        {
                            if (tileRow < 8)
                            {
                                offset = bankSelect | ((secondaryOam.at((i << 2) | 1) & 0xFE) << 4) + 7 - (tileRow & 0x07) | 16;
                            }
                            else
                            {
                                offset = bankSelect | ((secondaryOam.at((i << 2) | 1) & 0xFE) << 4) + 7 - (tileRow & 0x07);
                            }
                        }
                        else
                        {
                            if (tileRow < 8)
                            {
                                offset = bankSelect | ((secondaryOam.at((i << 2) | 1) & 0xFE) << 4) | (tileRow & 0x07);
                            }
                            else
                            {
                                offset = bankSelect | (((secondaryOam.at((i << 2) | 1) & 0xFE) + 1) << 4) | (tileRow & 0x07);
                            }
                        }

                        sprites[i].lsbShiftRegister = readPPU(offset + 0);
                        sprites[i].msbShiftRegister = readPPU(offset + 8);

                        sprites[i].attr = secondaryOam.at((i << 2) | 2);

                        if ((sprites[i].attr & 0x40))
                        {
                            sprites[i].lsbShiftRegister = reverseBitLookup[sprites[i].lsbShiftRegister];
                            sprites[i].msbShiftRegister = reverseBitLookup[sprites[i].msbShiftRegister];
                        }

                        sprites[i].xPosCounter = secondaryOam.at((i << 2) | 3);

                        sprites[i].active = false;
                        sprites[i].drawn = (i < found);
                    }
                }
                for (uint8_t i = found; i < 8; i++)
                {
                    sprites[i].lsbShiftRegister = 0;
                    sprites[i].msbShiftRegister = 0;
                    sprites[i].attr = 0;
                }
            }
        }
    }
    // Postrender scanline
    else if (scanline == 240)
    {
        // V-Sync
        if (pixel == 0)
        {
            secondBuffer = !secondBuffer;
            if (secondBuffer)
            {
                screen = screenBuf1;
                bufferedScreen = screenBuf0;
            }
            else
            {
                screen = screenBuf0;
                bufferedScreen = screenBuf1;
            }
        }
    }
    // vBlank scanlines
    else if (scanline >= 241 && scanline <= 260)
    {
        if (scanline == 241 && pixel == 1)
        {
            // Set vBlank
            vBlank = true;
            if (!suppressVblankSetting)
            {
                status |= STATUS_VBLANK;
            }
            else
                suppressVblankSetting = false;
        }
    }

    uint8_t finalPixel = 0x00;
    uint8_t finalPalette = 0x00;

    uint8_t bgPixel = 0x00;
    uint8_t bgPalette = 0x00;

    uint8_t spritePixel = 0x00;
    uint8_t spritePalette = 0x00;

    uint8_t spritePriority = 0x00;

    // If background rendering is enabled
    if (ppumask & MASK_SHOW_BACKGROUND && (pixel > 8 || (ppumask & MASK_SHOW_LEFT_BG)))
    {
        uint16_t bitMux = 0x8000 >> fineXScroll;

		uint8_t p0Pixel = ((shiftRegisterPatternLower & bitMux) > 0);
		uint8_t p1Pixel = ((shiftRegisterPatternHigher & bitMux) > 0);

		// Combine to form pixel index
		bgPixel = ((p1Pixel << 1) | p0Pixel);

		// Get palette
		uint8_t bgPal0 = ((shiftRegisterAttributeLower & bitMux) > 0);
		uint8_t bgPal1 = ((shiftRegisterAttributeHigher & bitMux) > 0);
		bgPalette = ((bgPal1 << 1) | bgPal0);
    }

    // If sprite rendering is enabled
    if ((ppumask & MASK_SHOW_SPRITES) && (pixel > 8 || (ppumask & MASK_SHOW_LEFT_SPRITES)))
    {
        zeroRendered = false;

        for (uint8_t i = 0; i < found; i++)
        {
            if (sprites[i].xPosCounter == 0)
            {
                uint8_t p0Pixel = sprites[i].lsbShiftRegister & 0x80;
                uint8_t p1Pixel = sprites[i].msbShiftRegister & 0x80;

                uint8_t candidatePixel = (p1Pixel >> 6) | (p0Pixel >> 7);

                if (candidatePixel != 0)
                {
                    if (i == 0)
                        zeroRendered = true;
                        
                    spritePixel = candidatePixel;
                    spritePalette = (sprites[i].attr & 0x03) | 0x04;
                    spritePriority = ((sprites[i].attr & 0x20) >> 4);

                    break;
                }
            }
        }
    }

    if (bgPixel == 0 && spritePixel == 0)
    {
        finalPixel = 0x00;
        finalPalette = 0x00;
    }
    else if (bgPixel == 0 && spritePixel > 0)
    {
        finalPixel = spritePixel;
        finalPalette = spritePalette;
    }
    else if (bgPixel > 0 && spritePixel == 0)
    {
        finalPixel = bgPixel;
        finalPalette = bgPalette;
    }
    else if (bgPixel > 0 && spritePixel > 0)
    {
        if (spritePriority == 0)
        {
            finalPixel = spritePixel;
            finalPalette = spritePalette;
        }
        else
        {
            finalPixel = bgPixel;
            finalPalette = bgPalette;
        }

        if (zeroStored && zeroRendered)
        {
            if (ppumask & MASK_RENDERING)
            {
                if (ppumask & (MASK_SHOW_LEFT_BG | MASK_SHOW_LEFT_SPRITES))
                {
                    if (pixel >= 1 && pixel < 256)
                        status |= STATUS_SPRITE_ZERO_HIT;
                }
                else
                {
                    if (pixel >= 9 && pixel < 256)
                        status |= STATUS_SPRITE_ZERO_HIT;
                }
            }
            zeroRendered = false;
        }
    }

    if (scanline >= 0 && scanline < 240 && pixel >= 1 && pixel <= 256)
        SetPixel(pixel - 1, scanline, GetColorForPixel(finalPixel, finalPalette));

    pixel++;

    if (ppumask & MASK_RENDERING)
    {
        if (pixel == 260 && scanline < 240 && cartridge != nullptr)
        {
            cartridge->scanlineCallback();
        }
    }

    if (pixel > 340)
    {
        pixel = 0;
        scanline++;
        if (scanline > 260)
        {
            scanline = -1;
            frame++;
            oddFrame = !oddFrame;
        }
    }
}

void PPU::reset()
{
    for (int i = 0; i < 256 * 240 * 3; i++)
        screenBuf0[i] = 0;

    vRamBank0.fill(0);
    vRamBank1.fill(0);

    paletteRam.fill(0);

    status = 0;
    control = 0;
    ppumask = 0;

    v = 0;
    t = 0;
    addressWriteLatch = false;
    fineXScroll = 0;

    scanline = 0;
    pixel = 0;

    frame = 0;
    oddFrame = false;

    shiftRegisterPatternLower = 0;
    shiftRegisterPatternHigher = 0;
    shiftRegisterAttributeLower = 0;
    shiftRegisterAttributeHigher = 0;

    oam.fill(0);
    oamAddr = 0;
    oamData = 0;
}

void PPU::SetArrangement(Mapper::Arrangement arr)
{
    switch (arr)
    {
        case Mapper::Arrangement::VERTICAL:
            windows[0] = &vRamBank0;
            windows[1] = &vRamBank0;
            windows[2] = &vRamBank1;
            windows[3] = &vRamBank1;
            break;
        case Mapper::Arrangement::HORIZONTAL:
            windows[0] = &vRamBank0;
            windows[1] = &vRamBank1;
            windows[2] = &vRamBank0;
            windows[3] = &vRamBank1;
            break;
        case Mapper::Arrangement::ONE_SCREEN_A:
            windows[0] = &vRamBank0;
            windows[1] = &vRamBank0;
            windows[2] = &vRamBank0;
            windows[3] = &vRamBank0;
            break;
        case Mapper::Arrangement::ONE_SCREEN_B:
            windows[0] = &vRamBank1;
            windows[1] = &vRamBank1;
            windows[2] = &vRamBank1;
            windows[3] = &vRamBank1;
            break;
    }
}