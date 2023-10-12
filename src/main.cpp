#include <iostream>
#include "../include/raylib.h"
#include <intrin.h>
#include <string>

#include "bus.hpp"
#include "cartridge.hpp"

#include "gui/button.hpp"

// Assets
#include "../assets/sprites/ArrowButton.h"
#include "../assets/sprites/PowerButton.h"
#include "../assets/sprites/ResetButton.h"
#include "../assets/sprites/F3Button.h"
#include "../assets/sprites/F4Button.h"
#include "../assets/sprites/GithubButton.h"
#include "../assets/sprites/WebpageButton.h"

#include "../assets/fonts/pixelnes.h"

std::vector<Button*> Button::buttons;

Bus bus;

uint8_t counter = 1;

#define LERP(a, b, t) a * (1 - t) + b * t
#define FRAC(a) a - (int)a

void Callback(void* buffer, unsigned int frames)
{
    if (!bus.init)
        return;

    uint16_t* buf = (uint16_t*) buffer;

    while (bus.mutex);
    bus.mutex = true;

    //float ratio = bus.audioBuffer.size() / frames;
    float ratio = 1;
    uint16_t previous = bus.audioBuffer.front();

    for (unsigned int i = 0; i < frames; i++)
    {
        if (ratio >= 1)
        {
            buf[i] = bus.audioBuffer.front();
            if (bus.audioBuffer.size() > 1)
            bus.audioBuffer.pop();
        }
        else
        {
            buf[i] = (uint16_t) LERP((float) previous, (float) bus.audioBuffer.front(), FRAC((float) i * ratio));

            if ((int)i * ratio < (int)(i + 1) * ratio)
            {
                previous = bus.audioBuffer.front();
                bus.audioBuffer.pop();
            }
        }
    }

    bus.mutex = false;
}

int main(int argc, char** argv)
{
    enum Menus
    {
        CARTRIDGE_INFO,
        INPUT,
        AUDIO,
        CPU_STATE,
        PATTERN_TABLE_A,
        PATTERN_TABLE_B,
        PALETTES,
        OAM,
        CREDITS
    };
    const int numberOfMenus = 9;
    std::string menuLabels[] = {
        "Cartridge info",
        "Input & Keys",
        "Audio",
        "CPU state",
        "Pattern table A",
        "Pattern table B",
        "Palette RAM",
        "OAM",
        "Credits"
    };
    
    std::string audioChannels[] = {
        "Square 1",
        "Square 2",
        "Triangle",
        "Noise",
        "DMC"
    };

    int menuNumber = 0;
    int menuChoice = 0;

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(912, 520, "RICOcHet");
    SetTargetFPS(60);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(128);
    AudioStream stream = LoadAudioStream(48000, 16, 1);
    bus.SetAudioFrequency(48000);

    SetAudioStreamCallback(stream, Callback);

    PlayAudioStream(stream);

    Font font = LoadFont_Pixelnes();

    Image img = GenImageColor(256, 240, BLACK);
    ImageFormat(&img, PixelFormat::PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    Cartridge *cartridge = nullptr;
    bus.reset();

    if (argc > 1)
    {
        std::string path = argv[1];

        cartridge = new Cartridge(path);

        if (!cartridge->IsRomValid())
        {
            delete cartridge;
            cartridge = nullptr;
        }
        else
        {
            bus.LoadRom(cartridge);
        }
    }

    Button powerButton(powerButtonData, false, 649, 464, KEY_P, [&]() {

    });
    Button resetButton(resetButtonData, false, 731, 464, KEY_R, [&]() { 
        bus.reset(); 
    });

    // Input
    bool toggleCompactView = false;
    bool toggleFullscreen = false;

    Button f3Button(f3ButtonData, false, 600, 230, KEY_F3, [&]() {
        toggleCompactView = true;
    });
    Button f4Button(f4ButtonData, false, 600, 280, KEY_F4, [&]() {
        toggleFullscreen = true;
    });

    // Credits
    Button githubButton(githubButtonData, false, 679, 220, KEY_NULL, [&]() {
        OpenURL("https://github.com/michelelorusso05");
    });
    Button webpageButton(webpageButtonData, false, 731, 220, KEY_NULL, [&]() {
        OpenURL("https://micheleprojects.altervista.org"); 
    });

    auto onMenuChanged = [&]()
    {
        f3Button.SetEnabled(false);
        f4Button.SetEnabled(false);

        githubButton.SetEnabled(false);
        webpageButton.SetEnabled(false);
    };

    Button leftArrow(arrowButtonData, false, 556, 124, KEY_LEFT, [&]() {
        menuNumber = (menuNumber == 0) ? (numberOfMenus - 1) : menuNumber - 1;
        onMenuChanged();
    });
    Button rightArrow(arrowButtonData, true, 856, 124, KEY_RIGHT, [&]() { 
        menuNumber = (menuNumber + 1) % numberOfMenus;
        onMenuChanged();
    });

    onMenuChanged();

    char t[64];

    bool expandedView = true;
    bool fullscreen = false;

    bool queueReturnFromFullscreen = false;
    int cachedMonitor = GetCurrentMonitor();

    SetExitKey(KEY_NULL);

    while (!WindowShouldClose())
    {
        if (IsFileDropped())
        {
            FilePathList list = LoadDroppedFiles();

            if (cartridge != nullptr)
                delete cartridge;

            cartridge = new Cartridge(list.paths[0]);
            if (!cartridge->IsRomValid())
            {
                delete cartridge;
                bus.reset();
                bus.UnloadRom();
                cartridge = nullptr;
            }
            else
            {
                bus.LoadRom(cartridge);
            }
            UnloadDroppedFiles(list);
        }

        if ((toggleCompactView || queueReturnFromFullscreen) && !fullscreen)
        {
            toggleCompactView = false;

            if (!queueReturnFromFullscreen)
                expandedView = !expandedView;

            if (expandedView)
            {
                SetWindowSize(912, 520);
                if (!queueReturnFromFullscreen)
                    SetWindowPosition(GetWindowPosition().x - (912 - 552) / 2, GetWindowPosition().y);
            }
            else
            {
                SetWindowSize(552, 520);
                if (!queueReturnFromFullscreen)
                    SetWindowPosition(GetWindowPosition().x + (912 - 552) / 2, GetWindowPosition().y);
            }

            queueReturnFromFullscreen = false;
        }
        else if (toggleFullscreen || (IsKeyPressed(KEY_ESCAPE) && fullscreen))
        {
            toggleFullscreen = false;

            fullscreen = !fullscreen;

            if (!fullscreen)
            {
                queueReturnFromFullscreen = true;
            }
            else
            {
                cachedMonitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(cachedMonitor), GetMonitorHeight(cachedMonitor));
            }
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_C))
        {
            bus.cpu.clockUntilInstruction();
        }
          
        if (true ^ IsKeyDown(KEY_SPACE))
        {
            for (int i = 0; i < ((MASTER_CLOCK / PPU_DIVIDER) / 60); i++)
            {
                bus.busClock();
            }
        }
        

        if (IsKeyDown(KEY_W))
            bus.SetButtonStatus(Controller::Buttons::Up, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Up, false);
        if (IsKeyDown(KEY_S))
            bus.SetButtonStatus(Controller::Buttons::Down, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Down, false);
        if (IsKeyDown(KEY_A))
            bus.SetButtonStatus(Controller::Buttons::Left, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Left, false);
        if (IsKeyDown(KEY_D))
            bus.SetButtonStatus(Controller::Buttons::Right, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Right, false);

        if (IsKeyDown(KEY_BACKSPACE))
            bus.SetButtonStatus(Controller::Buttons::Select, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Select, false);
        if (IsKeyDown(KEY_ENTER))
            bus.SetButtonStatus(Controller::Buttons::Start, true);
        else
            bus.SetButtonStatus(Controller::Buttons::Start, false);

        if (IsKeyDown(KEY_K))
            bus.SetButtonStatus(Controller::Buttons::B, true);
        else
            bus.SetButtonStatus(Controller::Buttons::B, false);
        if (IsKeyDown(KEY_L))
            bus.SetButtonStatus(Controller::Buttons::A, true);
        else
            bus.SetButtonStatus(Controller::Buttons::A, false);

        BeginDrawing();
            UpdateTexture(texture, bus.ppu.GetScreen());

            // Forced update for buttons that need to fire callbacks even when disabled
            f3Button.Update();
            f4Button.Update();
            resetButton.Update();

            if (fullscreen)
            {
                ClearBackground(BLACK);
                DrawFPS(10, 10);
                int width = GetMonitorWidth(cachedMonitor);
                float scale = ((float) GetMonitorHeight(cachedMonitor)) / 240.0f;
                DrawTextureEx(texture, Vector2{width / 2 - 256 * scale / 2, 0}, 0, scale, WHITE);
            }
            else
            {
                ClearBackground(RAYWHITE);
                if (expandedView)
                {
                    switch (menuNumber)
                    {
                        case CARTRIDGE_INFO:
                            if (bus.isRomLoaded)
                            {
                                DrawTextEx(font, "Filename: ", Vector2{600, 60}, 16, 1, GRAY);
                                DrawTextEx(font, bus.rom->GetFilename().c_str(), Vector2{600, 80}, 20, 1, BLACK);

                                DrawTextEx(font, "PRG-ROM: ", Vector2{600, 110}, 16, 1, GRAY);
                                sprintf(t, "%dKB", bus.rom->header.prgRomBanks * 16);
                                DrawTextEx(font, t, Vector2{600, 130}, 20, 1, BLACK);

                                DrawTextEx(font, "CHR-ROM: ", Vector2{600, 160}, 16, 1, GRAY);
                                uint8_t nBanks = bus.rom->header.chrRomBanks;
                                if (nBanks == 0)
                                {
                                    DrawTextEx(font, "8KB CHR-RAM", Vector2{600, 180}, 20, 1, BLACK);
                                }
                                else
                                {
                                    sprintf(t, "%dKB", bus.rom->header.chrRomBanks * 8);
                                    DrawTextEx(font, t, Vector2{600, 180}, 20, 1, BLACK);
                                }

                                DrawTextEx(font, "Mapper: ", Vector2{600, 210}, 16, 1, GRAY);
                                if (Cartridge::IsMapperSupported(bus.rom->mapperID))
                                {
                                    sprintf(t, "%d - %s", bus.rom->mapperID, bus.rom->GetMapperName().c_str());
                                    DrawTextEx(font, t, Vector2{600, 230}, 20, 1, BLACK);
                                }
                                else
                                {
                                    sprintf(t, "%d (using mapper 0)", bus.rom->mapperID);
                                    DrawTextEx(font, t, Vector2{600, 230}, 20, 1, RED);
                                }

                                if (bus.rom->IsVsGame())
                                {
                                    DrawTextEx(font, "Notes: ", Vector2{600, 260}, 16, 1, GRAY);
                                    DrawTextEx(font, "VS. System games are\nnot supported", Vector2{600, 280}, 16, 1, RED);
                                }
                                else if (bus.rom->HasSave())
                                {
                                    DrawTextEx(font, "Savefile: ", Vector2{600, 260}, 16, 1, GRAY);
                                    sprintf(t, "Savedata stored in\n%s.nes.sav", bus.rom->GetFilename().c_str());
                                    DrawTextEx(font, t, Vector2{600, 280}, 16, 1, BLACK);
                                }
                            }
                            else
                            {
                                DrawTextEx(font, "No ROM loaded", Vector2{600, 60}, 16, 1, GRAY);
                                DrawTextEx(font, "Drag a .nes file here\nto start playing", Vector2{600, 80}, 16, 1, GRAY);
                            }
                            break;
                        case INPUT:
                            f3Button.SetEnabled(true);
                            f4Button.SetEnabled(true);

                            DrawTextEx(font, "Player 1", Vector2{600, 60}, 16, 1, GRAY);
                            DrawTextEx(font, "Keyboard", Vector2{600, 80}, 20, 1, BLACK);

                            DrawTextEx(font, "Player 2", Vector2{600, 110}, 16, 1, GRAY);
                            DrawTextEx(font, "po s penz", Vector2{600, 130}, 20, 1, BLACK);

                            DrawTextEx(font, "Other keybindings", Vector2{600, 210}, 16, 1, GRAY);
                            DrawTextEx(font, "Toggle\ncompact view", Vector2{650, 235}, 20, 1, BLACK);
                            DrawTextEx(font, "Toggle\nfullscreen", Vector2{650, 285}, 20, 1, BLACK);
                            break;
                        case AUDIO:
                            for (int i = 0; i < 5; i++)
                            {
                                double output = bus.apu.getDebugOutput(i);

                                DrawTextEx(font, audioChannels[i].c_str(), Vector2{600, 60.0f + 50 * i}, 16, 1, BLACK);
                                DrawRectangle(600, 80 + 50 * i, 252, 24, DARKGRAY);
                                DrawRectangle(602, 82 + 50 * i, 248, 16, GRAY);
                                DrawRectangle(602, 98 + 50 * i, 248, 4, GetColor(0x6F6F6FFF));

                                Color c = bus.ppu.getColorFromPaletteAddress(0x03 + 0x04 * i);
                                DrawRectangle(602, 82 + 50 * i, 248 * output, 16, c);

                                uint32_t intColor = ColorToInt(c);
                                uint32_t darkenedColor = 0xFF;
                                for (int j = 3; j > 0; j--)
                                {
                                    uint16_t component = ((intColor >> (8 * j)) & 0xFF);
                                    component *= 0.75;
                                    darkenedColor |= (component << (8 * j));
                                }

                                DrawRectangle(602, 98 + 50 * i, 248 * output, 4, GetColor(darkenedColor));
                            }
                            
                            break;
                        case CPU_STATE:
                        {
                            sprintf(t, "0x%02X\0", bus.cpu.ax);
                            DrawTextEx(font, "AX", Vector2{ 600, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 600, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.rx);
                            DrawTextEx(font, "RX", Vector2{ 697, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 697, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.ry);
                            DrawTextEx(font, "RY", Vector2{ 794, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 794, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%04X\0", bus.cpu.pc);
                            DrawTextEx(font, "PC", Vector2{ 600, 110 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 600, 130 }, 20, 1, BLACK);

                            sprintf(t, "0x%04X\0", bus.cpu.sp);
                            DrawTextEx(font, "SP", Vector2{ 766, 110 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 766, 130 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X: %s\0", bus.cpu.opcode, (*(bus.cpu.GetMnemonicForOpcode(bus.cpu.opcode))).c_str());
                            DrawTextEx(font, "Last executed opcode", Vector2{ 600, 160 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 600, 180 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.status);
                            DrawTextEx(font, "Status register", Vector2{ 600, 210 }, 16, 1, GRAY);
                            DrawTextEx(font, "N V U B D I Z C", Vector2{ 600, 230 }, 20, 1, BLACK);
                            
                            for (int i = 0; i < 8; i++)
                            {
                                if (bus.cpu.status & (0x80 >> i))
                                    DrawRectangle(600 + 28 * i, 250, 12, 4, BLACK);
                            }

                            break;
                        }
                        case PATTERN_TABLE_A:
                            bus.ppu.drawPatternTable(596, 60, 0);
                            break;
                        case PATTERN_TABLE_B:
                            bus.ppu.drawPatternTable(596, 60, 1);
                            break;
                        case PALETTES:
                            DrawTextEx(font, "Background", Vector2{597, 60}, 16, 1, BLACK);
                            for (int i = 0; i < 4; i++)
                            {
                                bus.ppu.drawPalette(603, 80 + 26 * i, i);
                            }

                            DrawTextEx(font, "Sprites", Vector2{754, 60}, 16, 1, BLACK);
                            for (int i = 0; i < 4; i++)
                            {
                                bus.ppu.drawPalette(741, 80 + 26 * i, i | 4);
                            }
                            break;
                        case OAM:
                            DrawTextEx(font, "Primary", Vector2{686, 60}, 16, 1, BLACK);
                            bus.ppu.drawOAM(660, 80);

                            DrawTextEx(font, "Secondary", Vector2{674, 208}, 16, 1, BLACK);
                            bus.ppu.drawSecondaryOAM(660, 228);
                            break;
                        case CREDITS:
                            githubButton.SetEnabled(true);
                            webpageButton.SetEnabled(true);

                            DrawTextEx(font, "What", Vector2{600, 60}, 16, 1, GRAY);
                            DrawTextEx(font, "RICOcHet NES emulator", Vector2{600, 80}, 18, 1, BLACK);

                            DrawTextEx(font, "Who", Vector2{600, 110}, 16, 1, GRAY);
                            DrawTextEx(font, "Michele Lorusso", Vector2{600, 130}, 20, 1, BLACK);

                            DrawTextEx(font, "When", Vector2{600, 160}, 16, 1, GRAY);
                            DrawTextEx(font, "Built 12/09/2023", Vector2{600, 180}, 20, 1, BLACK);

                            break;
                    }      
                }

                DrawTextureEx(texture, Vector2{ 20, 20 }, 0, 2, WHITE);

                DrawRectangle(20, 20, 4, 2, RAYWHITE);
                DrawRectangle(20, 20, 2, 4, RAYWHITE);

                DrawRectangle(20 + 512 - 4, 20, 4, 2, RAYWHITE);
                DrawRectangle(20 + 512 - 2, 20, 2, 4, RAYWHITE);

                DrawRectangle(20, 20 + 480 - 2, 4, 2, RAYWHITE);
                DrawRectangle(20, 20 + 480 - 4, 2, 4, RAYWHITE);

                DrawRectangle(20 + 512 - 4, 20 + 480 - 2, 4, 2, RAYWHITE);
                DrawRectangle(20 + 512 - 2, 20 + 480 - 4, 2, 4, RAYWHITE);

                DrawTextEx(font, menuLabels[menuNumber].c_str(), Vector2{724 - MeasureTextEx(font, menuLabels[menuNumber].c_str(), 24, 1).x / 2, 20}, 24, 1, BLACK);

                
                for (Button* button : Button::buttons)
                    button->Update();

                for (Button* button : Button::buttons)
                    button->Render();
            }


        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadFont(font);

    powerButton.~Button();

    CloseWindow();

    if (cartridge != nullptr)
        delete cartridge;

    return 0;
}