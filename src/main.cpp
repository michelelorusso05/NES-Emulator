#include <iostream>
#include "../include/raylib.h"
#include "../include/tinyfiledialogs.h"
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
#include "../assets/sprites/MButton.h"
#include "../assets/sprites/OButton.h"

#include "../assets/fonts/PixelNES.h"

#include "../assets/icon.h"

std::vector<Button*> Button::buttons;

Bus bus;
AudioStream stream;

uint64_t underruns = 0;
int audioFrequency = SAMPLING_FREQUENCY;

#define LERP(a, b, t) a * (1 - t) + b * t
#define FRAC(a) a - (int)a
#define ROUND(a) ((FRAC(a) >= 0.5f) ? (((int) a) + 1) : ((int) a))

void Callback(void* buffer, unsigned int frames)
{
    int16_t* stream = reinterpret_cast<int16_t*>(buffer);

    size_t numSamplesToRead = frames;

    bus.mutex = true;

    size_t numSamplesRead = bus.audioBuffer.PopBack(stream, numSamplesToRead);
    // Fill any spaces left empty by underruns with the last generated sample
    if (numSamplesRead < numSamplesToRead)
    {
        // If we didn't generate any sample (yikes) just fill in zeroes
        int16_t lastSample = numSamplesRead == 0 ? 0 : stream[numSamplesRead - 1];
        std::fill_n(stream + numSamplesRead, numSamplesToRead - numSamplesRead, lastSample);

        underruns++;
    }

    bus.mutex = false;
}

int keyboardMappings[8] =
{
    KEY_L,
    KEY_K,
    KEY_BACKSPACE,
    KEY_ENTER,
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D
};

int gamepadMappings[8] =
{
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
    GAMEPAD_BUTTON_MIDDLE_LEFT,
    GAMEPAD_BUTTON_MIDDLE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_UP,
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT
};

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
        PPU_MEMORY,
        CREDITS
    };
    const int numberOfMenus = 8;
    std::string menuLabels[] = {
        "Cartridge info",
        "Input & Keys",
        "Audio",
        "CPU state",
        "Pattern table A",
        "Pattern table B",
        "PPU Memory Bus",
        "Credits"
    };
    
    std::string audioChannels[] = {
        "Square 1",
        "Square 2",
        "Triangle",
        "Noise",
        "DMC (not implemented)"
    };

    char cpuFlagsString[16] = "N\0V\0-\0B\0D\0I\0Z\0C";

    int menuNumber = 0;
    int menuChoice = 0;

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(924, 520, "RICOcHet");
    SetTargetFPS(60);

    Image temp = { 0 };
    temp.data = ICON_DATA;
    temp.format = ICON_FORMAT;
    temp.height = ICON_WIDTH;
    temp.width = ICON_HEIGHT;
    temp.mipmaps = 1;

    Texture2D iconTex = LoadTextureFromImage(temp);

    //ImageResize(&temp, 128, 128);

    SetWindowIcon(temp);
    //UnloadImage(temp);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(512);
    stream = LoadAudioStream(audioFrequency, 16, 1);
    bus.SetAudioFrequency(audioFrequency);

    bool waitForAudioBufferFill = true;

    PauseAudioStream(stream);
    SetAudioStreamCallback(stream, Callback);

    Font font = LoadFont_PixelNES();

    Image img = GenImageColor(256, 240, BLACK);
    ImageFormat(&img, PixelFormat::PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    Cartridge *cartridge = nullptr;
    bus.reset();

    // Load ROM from command line
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

    Button powerButton(powerButtonData, false, 652, 464, KEY_P, [&]() {

    });
    Button resetButton(resetButtonData, false, 738, 464, KEY_R, [&]() { 
        bus.reset(); 
    });

    // Input
    bool toggleCompactView = false;
    bool toggleFullscreen = false;

    Button f3Button(f3ButtonData, false, 602, 352, KEY_F3, [&]() {
        toggleCompactView = true;
    });
    Button f4Button(f4ButtonData, false, 602, 402, KEY_F4, [&]() {
        toggleFullscreen = true;
    });

    const char* filters[1] = {
        "*.nes"
    };

    Button selectRomButton(oButtonData, false, 602, 402, KEY_O, [&]() {
        PauseAudioStream(stream);
        waitForAudioBufferFill = true;
        const char* file = tinyfd_openFileDialog("Load NES rom", GetApplicationDirectory(), 1, filters, NULL, 0);
        
        if (file != NULL)
        {
            if (cartridge != nullptr)
                delete cartridge;

            cartridge = new Cartridge(file);
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
        }
    });

    bool mute = false;

    Button muteButton(mButtonData, false, 602, 402, KEY_M, [&]() {
        mute = !mute;
        SetAudioStreamVolume(stream, mute ? 0 : 1);
    });

    // Credits
    Button githubButton(githubButtonData, false, 682, 251, KEY_NULL, [&]() {
        OpenURL("https://github.com/michelelorusso05");
    });
    Button webpageButton(webpageButtonData, false, 738, 251, KEY_NULL, [&]() {
        OpenURL("https://micheleprojects.altervista.org"); 
    });

    auto onMenuChanged = [&]()
    {
        f3Button.SetEnabled(false);
        f4Button.SetEnabled(false);
        selectRomButton.SetEnabled(false);
        muteButton.SetEnabled(false);

        githubButton.SetEnabled(false);
        webpageButton.SetEnabled(false);
    };

    Button leftArrow(arrowButtonData, false, 556, 188, KEY_LEFT, [&]() {
        menuNumber = (menuNumber == 0) ? (numberOfMenus - 1) : menuNumber - 1;
        onMenuChanged();
    });
    Button rightArrow(arrowButtonData, true, 868, 188, KEY_RIGHT, [&]() { 
        menuNumber = (menuNumber + 1) % numberOfMenus;
        onMenuChanged();
    });

    onMenuChanged();

    // Common buffer for text formatting
    char t[64];

    // String buffers for controller names
    std::string p1String;
    std::string p2String;

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
                SetWindowSize(924, 520);
                if (!queueReturnFromFullscreen)
                    SetWindowPosition(GetWindowPosition().x - (924 - 552) / 2, GetWindowPosition().y);
            }
            else
            {
                SetWindowSize(552, 520);
                if (!queueReturnFromFullscreen)
                    SetWindowPosition(GetWindowPosition().x + (924 - 552) / 2, GetWindowPosition().y);
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
            waitForAudioBufferFill = true;
            PauseAudioStream(stream);
        }

        if (IsKeyPressed(KEY_C))
        {
            bus.cpu.clockUntilInstruction();
        }
          
        if (!IsKeyDown(KEY_SPACE))
        {
            if (!waitForAudioBufferFill)
                ResumeAudioStream(stream);
            // PPU frames are aligned to real frames
            while (!bus.busClock());
        }
        else
            PauseAudioStream(stream);

        if (IsKeyPressed(KEY_UP))
        {
            audioFrequency += 10;
            bus.SetAudioFrequency(audioFrequency);
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            audioFrequency -= 10;
            bus.SetAudioFrequency(audioFrequency);
        }

        if (IsGamepadAvailable(0))
        {
            const char* name = GetGamepadName(0);
            if (name != nullptr)
            {
                p1String = name;
                p1String = p1String.substr(0, 16).append("...");
            }

            p2String = "Keyboard";

            for (int i = 0; i < 8; i++)
            {
                bus.SetButtonStatusPlayer1((Controller::Buttons)(1 << i), IsGamepadButtonDown(0, gamepadMappings[i]));
                bus.SetButtonStatusPlayer2((Controller::Buttons)(1 << i), IsKeyDown(keyboardMappings[i]));
            }

            float x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
            float y = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

            if (x >= 0.2)
                bus.SetButtonStatusPlayer1(Controller::Buttons::Right, true);
            if (x <= -0.2)
                bus.SetButtonStatusPlayer1(Controller::Buttons::Left, true);
            if (y >= 0.2)
                bus.SetButtonStatusPlayer1(Controller::Buttons::Down, true);
            if (y <= -0.2)
                bus.SetButtonStatusPlayer1(Controller::Buttons::Up, true);
        }
        else
        {
            p1String = "Keyboard";

            for (int i = 0; i < 8; i++)
                bus.SetButtonStatusPlayer1((Controller::Buttons)(1 << i), IsKeyDown(keyboardMappings[i]));
        }
        if (IsGamepadAvailable(1))
        {
            const char* name = GetGamepadName(1);
            if (name != nullptr)
            {
                p2String = name;
                p2String = p2String.substr(0, 16).append("...");
            }

            for (int i = 0; i < 8; i++)
                bus.SetButtonStatusPlayer2((Controller::Buttons)(1 << i), IsGamepadButtonDown(1, gamepadMappings[i]));
            
            float x = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);
            float y = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y);

            if (x >= 0.4)
                bus.SetButtonStatusPlayer2(Controller::Buttons::Right, true);
            if (x <= -0.4)
                bus.SetButtonStatusPlayer2(Controller::Buttons::Left, true);
            if (y >= 0.4)
                bus.SetButtonStatusPlayer2(Controller::Buttons::Down, true);
            if (y <= -0.4)
                bus.SetButtonStatusPlayer2(Controller::Buttons::Up, true);
        }
        else if (!IsGamepadAvailable(0))
        {
            p2String = "None";
        }

        BeginDrawing();
            UpdateTexture(texture, bus.ppu.GetScreen());

            // Forced update for buttons that need to fire callbacks even when disabled
            f3Button.Update();
            f4Button.Update();
            resetButton.Update();
            selectRomButton.Update();
            muteButton.Update();

            if (fullscreen)
            {
                ClearBackground(bus.ppu.getColorFromPaletteAddress(0x00));
                //ClearBackground(BLACK);
                HideCursor();
                int width = GetMonitorWidth(cachedMonitor);
                float scale = ((float) GetMonitorHeight(cachedMonitor)) / 240.0f;
                DrawTextureEx(texture, Vector2{width / 2 - 256 * scale / 2, 0}, 0, scale, WHITE);
            }
            else
            {
                ClearBackground(RAYWHITE);
                ShowCursor();
                if (expandedView)
                {
                    // Draw debug layout lines
                    /*
                    if (mute)
                    {
                        DrawRectangleLines(556, 20, 348, 444, GRAY);
                        DrawRectangleLines(602, 20, 256, 444, GRAY);
                        DrawLine(730, 20, 730, 464, GRAY);
                        DrawLine(729, 20, 729, 464, GRAY);
                    }
                    */

                    switch (menuNumber)
                    {
                        case CARTRIDGE_INFO:
                        {
                            if (bus.isRomLoaded)
                            {
                                DrawTextEx(font, "Filename: ", Vector2{602, 60}, 16, 1, GRAY);
                                DrawTextEx(font, bus.rom->GetFilename().c_str(), Vector2{602, 80}, 20, 1, BLACK);

                                DrawTextEx(font, "PRG-ROM: ", Vector2{602, 110}, 16, 1, GRAY);
                                sprintf(t, "%dKB", bus.rom->header.prgRomBanks * 16);
                                DrawTextEx(font, t, Vector2{602, 130}, 20, 1, BLACK);

                                DrawTextEx(font, "CHR-ROM: ", Vector2{602, 160}, 16, 1, GRAY);
                                uint8_t nBanks = bus.rom->header.chrRomBanks;
                                if (nBanks == 0)
                                {
                                    sprintf(t, "%dKB CHR-RAM", 8);
                                    DrawTextEx(font, t, Vector2{602, 180}, 20, 1, BLACK);
                                }
                                else
                                {
                                    sprintf(t, "%dKB", bus.rom->header.chrRomBanks * 8);
                                    DrawTextEx(font, t, Vector2{602, 180}, 20, 1, BLACK);
                                }

                                DrawTextEx(font, "Mapper: ", Vector2{602, 210}, 16, 1, GRAY);
                                if (bus.rom->IsMapperSupported())
                                {
                                    sprintf(t, "%d - %s", bus.rom->mapperID, bus.rom->GetMapperName().c_str());
                                    DrawTextEx(font, t, Vector2{602, 230}, 20, 1, BLACK);
                                }
                                else
                                {
                                    sprintf(t, "%d", bus.rom->mapperID);
                                    DrawTextEx(font, t, Vector2{602, 230}, 20, 1, RED);
                                }


                                if (!bus.rom->IsMapperSupported())
                                {
                                    DrawTextEx(font, "Notes: ", Vector2{602, 260}, 16, 1, GRAY);
                                    DrawTextEx(font, "This mapper is\nnot supported\n(trying to use mapper 0)", Vector2{602, 280}, 16, 1, RED);
                                }
                                else if (bus.rom->IsVsGame())
                                {
                                    DrawTextEx(font, "Notes: ", Vector2{602, 260}, 16, 1, GRAY);
                                    DrawTextEx(font, "VS. System games are\nnot supported", Vector2{602, 280}, 16, 1, RED);
                                }
                                else if (bus.rom->IsPALGame())
                                {
                                    DrawTextEx(font, "Notes: ", Vector2{602, 260}, 16, 1, GRAY);
                                    DrawTextEx(font, "PAL games may not\nfunction correctly", Vector2{602, 280}, 16, 1, RED);
                                }
                                else if (bus.rom->IsNES2Header())
                                {
                                    DrawTextEx(font, "Notes: ", Vector2{602, 260}, 16, 1, GRAY);
                                    DrawTextEx(font, "NES 2.0 is not supported.\nThe game may not work", Vector2{602, 280}, 16, 1, RED);
                                }
                                else if (bus.rom->HasSave())
                                {
                                    DrawTextEx(font, "Savefile: ", Vector2{602, 260}, 16, 1, GRAY);
                                    sprintf(t, "Savedata stored in\n%s.nes.sav", bus.rom->GetFilename().c_str());
                                    DrawTextEx(font, t, Vector2{602, 280}, 16, 1, BLACK);
                                }
                            }
                            else
                            {
                                DrawTextEx(font, "No ROM loaded", Vector2{602, 60}, 16, 1, GRAY);
                                DrawTextEx(font, "Drag a .nes file here\nto start playing\nor select a ROM with\nthe button below", Vector2{602, 80}, 16, 1, GRAY);
                            }

                            selectRomButton.SetEnabled(true);
                            DrawTextEx(font, "Open a\n.nes file", Vector2{650, 407}, 20, 1, BLACK);
                            break;
                        }
                        case INPUT:
                        {
                            f3Button.SetEnabled(true);
                            f4Button.SetEnabled(true);

                            DrawTextEx(font, "Player 1", Vector2{602, 60}, 16, 1, GRAY);
                            DrawTextEx(font, p1String.c_str(), Vector2{602, 80}, 20, 1, BLACK);

                            DrawTextEx(font, "Player 2", Vector2{602, 110}, 16, 1, GRAY);
                            DrawTextEx(font, p2String.c_str(), Vector2{602, 130}, 20, 1, BLACK);

                            DrawTextEx(font, "Other keybindings", Vector2{602, 332}, 16, 1, GRAY);
                            DrawTextEx(font, "Toggle\ncompact view", Vector2{650, 357}, 20, 1, BLACK);
                            DrawTextEx(font, "Toggle\nfullscreen", Vector2{650, 407}, 20, 1, BLACK);
                            break;
                        }
                        case AUDIO:
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                double output = bus.apu.getDebugOutput(i);

                                DrawTextEx(font, audioChannels[i].c_str(), Vector2{602, 60.0f + 50 * i}, 16, 1, BLACK);
                                DrawRectangle(602, 80 + 50 * i, 256, 24, DARKGRAY);
                                DrawRectangle(604, 82 + 50 * i, 252, 16, GRAY);
                                DrawRectangle(604, 98 + 50 * i, 252, 4, GetColor(0x6F6F6FFF));

                                Color c = bus.ppu.getColorFromPaletteAddress(0x03 + 0x04 * i);
                                DrawRectangle(604, 82 + 50 * i, 252 * output, 16, c);

                                uint32_t intColor = ColorToInt(c);
                                uint32_t darkenedColor = 0xFF;
                                for (int j = 3; j > 0; j--)
                                {
                                    uint16_t component = ((intColor >> (8 * j)) & 0xFF);
                                    component *= 0.75;
                                    darkenedColor |= (component << (8 * j));
                                }

                                DrawRectangle(604, 98 + 50 * i, 252 * output, 4, GetColor(darkenedColor));

                            }

                            sprintf(t, "Sample frequency: %dHz", audioFrequency);
                            DrawTextEx(font, t, Vector2{602, 330}, 16, 1, BLACK);
                            sprintf(t, "Buffer status: %d/%d", bus.audioBuffer.UsedSize(), bus.audioBuffer.TotalSize());
                            DrawTextEx(font, t, Vector2{602, 350}, 16, 1, BLACK);
                            sprintf(t, "Underruns: %d", underruns);
                            DrawTextEx(font, t, Vector2{602, 370}, 16, 1, RED);

                            muteButton.SetEnabled(true);
                            DrawTextEx(font, "Toggle\nmute", Vector2{650, 407}, 20, 1, BLACK);
                            
                            break;
                        }
                        case CPU_STATE:
                        {
                            sprintf(t, "0x%02X\0", bus.cpu.ax);
                            DrawTextEx(font, "AX", Vector2{ 602, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 602, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.rx);
                            DrawTextEx(font, "RX", Vector2{ 702, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 702, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.ry);
                            DrawTextEx(font, "RY", Vector2{ 802, 60 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 802, 80 }, 20, 1, BLACK);

                            sprintf(t, "0x%04X\0", bus.cpu.pc);
                            DrawTextEx(font, "PC", Vector2{ 602, 110 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 602, 130 }, 20, 1, BLACK);

                            sprintf(t, "0x%04X\0", bus.cpu.sp);
                            DrawTextEx(font, "SP", Vector2{ 774, 110 }, 16, 1, GRAY);
                            DrawTextEx(font, t, Vector2{ 774, 130 }, 20, 1, BLACK);

                            sprintf(t, "0x%02X\0", bus.cpu.status);
                            DrawTextEx(font, "Status register", Vector2{ 602, 160 }, 16, 1, GRAY);

                            for (int i = 0; i < 8; i++)
                            {
                                DrawTextEx(font, (cpuFlagsString + (i << 1)), Vector2{ (602.0f + 26 * i), 180 }, 20, 1, BLACK);

                                if (bus.cpu.status & (0x80 >> i))
                                    DrawRectangle(602 + 26 * i - 1, 200, 13, 4, BLACK);
                            }

                            DrawTextEx(font, "Disassembler", Vector2{ 602, 210 }, 16, 1, GRAY);
                            DrawTextEx(font, bus.cpu.GetDisassembledInstructions(10).c_str(), Vector2{ 602, 230 }, 16, 1, BLACK);

                            break;
                        }
                        case PATTERN_TABLE_A:
                        {
                            bus.ppu.drawPatternTable(602, 94, 0);
                            break;
                        }
                        case PATTERN_TABLE_B:
                        {
                            bus.ppu.drawPatternTable(602, 94, 1);
                            break;
                        }
                        case PPU_MEMORY:
                        {
                            DrawTextEx(font, "Palette memory", Vector2{632, 60}, 20, 1, BLACK);
                            DrawLineEx(Vector2{602, 70}, Vector2{628, 70}, 2, BLACK);
                            DrawLineEx(Vector2{832, 70}, Vector2{858, 70}, 2, BLACK);
                            DrawTextEx(font, "Background", Vector2{613, 90}, 16, 1, BLACK);
                            for (int i = 0; i < 4; i++)
                            {
                                bus.ppu.drawPalette(618, 110 + 26 * i, i);
                            }

                            DrawTextEx(font, "Sprites", Vector2{750, 90}, 16, 1, BLACK);
                            for (int i = 0; i < 4; i++)
                            {
                                bus.ppu.drawPalette(738, 110 + 26 * i, i | 4);
                            }

                            DrawTextEx(font, "OAM", Vector2{709, 225}, 20, 1, BLACK);
                            DrawLineEx(Vector2{602, 235}, Vector2{704, 235}, 2, BLACK);
                            DrawLineEx(Vector2{756, 235}, Vector2{858, 235}, 2, BLACK);
                            DrawTextEx(font, "Primary", Vector2{690, 255}, 16, 1, BLACK);
                            bus.ppu.drawOAM(666, 275);

                            DrawTextEx(font, "Secondary", Vector2{679, 410}, 16, 1, BLACK);
                            bus.ppu.drawSecondaryOAM(666, 430);
                            break;
                        }
                        case CREDITS:
                        {
                            githubButton.SetEnabled(true);
                            webpageButton.SetEnabled(true);

                            DrawTextureEx(iconTex, Vector2{622, 151}, 0, 2, WHITE);
                            DrawTextEx(font, "RICOcHet", Vector2{694, 151}, 24, 1, BLACK);
                            DrawTextEx(font, "By Michele\nLorusso", Vector2{694, 181}, 16, 1, GRAY); 
                            DrawTextEx(font, "1.0 - 13/11/2023", Vector2{636, 225}, 16, 1, GRAY);

                            break;
                        }
                    }      
                }

                // Draw screen
                DrawTextureEx(texture, Vector2{ 20, 20 }, 0, 2, WHITE);

                // Draw top-left clipping
                DrawRectangle(20, 20, 4, 2, RAYWHITE);
                DrawRectangle(20, 20, 2, 4, RAYWHITE);
                // Draw top-right clipping
                DrawRectangle(20 + 512 - 4, 20, 4, 2, RAYWHITE);
                DrawRectangle(20 + 512 - 2, 20, 2, 4, RAYWHITE);
                // Draw bottom-left clipping
                DrawRectangle(20, 20 + 480 - 2, 4, 2, RAYWHITE);
                DrawRectangle(20, 20 + 480 - 4, 2, 4, RAYWHITE);
                // Draw bottom-right clipping
                DrawRectangle(20 + 512 - 4, 20 + 480 - 2, 4, 2, RAYWHITE);
                DrawRectangle(20 + 512 - 2, 20 + 480 - 4, 2, 4, RAYWHITE);

                DrawTextEx(font, menuLabels[menuNumber].c_str(), Vector2{730 - MeasureTextEx(font, menuLabels[menuNumber].c_str(), 24, 1).x / 2, 20}, 24, 1, BLACK);

                
                for (Button* button : Button::buttons)
                    button->Update();

                for (Button* button : Button::buttons)
                    button->Render();
            }


        EndDrawing();

        if (bus.audioBuffer.UsedSize() > AUDIO_BUFFER_SIZE / 2)
        {
            PlayAudioStream(stream);
            waitForAudioBufferFill = false;
        }

        // Dynamically change the sampling frequency to avoid underruns and overruns
        audioFrequency = LERP(audioFrequency, (SAMPLING_FREQUENCY + (AUDIO_BUFFER_SIZE / 2 - bus.audioBuffer.UsedSize())), (1.0f/GetFPS()));
        // Limit the change to +/- 500Hz to avoid drastic changes in pitch
        audioFrequency = (audioFrequency > SAMPLING_FREQUENCY + 500) ? (SAMPLING_FREQUENCY + 500) : audioFrequency;
        audioFrequency = (audioFrequency < SAMPLING_FREQUENCY - 500) ? (SAMPLING_FREQUENCY - 500) : audioFrequency;
        bus.SetAudioFrequency(audioFrequency);
    }

    UnloadTexture(texture);
    UnloadTexture(iconTex);

    Button::ClearButtons();

    CloseWindow();

    if (cartridge != nullptr)
        delete cartridge;

    return 0;
}