#include "../../include/raylib.h"
#include "../../assets/sprites/ButtonTexture.h"
#include <string>
#include <functional>
#include <vector>

#define BUTTON_SCALE 2

class Button
{
public:
    static std::vector<Button *> buttons;

    Button(std::string filename, bool reverseX, int x, int y, int associatedKey, std::function<void(void)> action)
    {
        Image temp = LoadImage(filename.c_str());

        if (reverseX)
            ImageFlipHorizontal(&temp);

        normal = LoadTextureFromImage(temp);
        UnloadImage(temp);

        temp = LoadImage(filename.insert(filename.length() - 4, "Pressed").c_str());

        if (reverseX)
            ImageFlipHorizontal(&temp);

        pressed = LoadTextureFromImage(temp);
        UnloadImage(temp);

        position = Vector2{(float) x, (float) y};

        state = &normal;
        mappedKey = associatedKey;
        callback = action;

        buttons.push_back(this);
    }
    Button(ButtonTexture data, bool reverseX, int x, int y, int associatedKey, std::function<void(void)> action)
    {
        Image temp = { 0 };
        temp.data = data.normalState;
        temp.format = data.format;
        temp.height = data.height;
        temp.width = data.width;
        temp.mipmaps = 1;

        if (reverseX)
            ImageFlipHorizontal(&temp);

        normal = LoadTextureFromImage(temp);
        UnloadImage(temp);

        temp.data = data.pressedState;

        if (reverseX)
            ImageFlipHorizontal(&temp);

        pressed = LoadTextureFromImage(temp);
        UnloadImage(temp);

        position = Vector2{(float) x, (float) y};

        state = &normal;
        mappedKey = associatedKey;
        callback = action;

        buttons.push_back(this);
    }
    Button(std::string filename, bool reverseX, int x, int y, std::function<void(void)> action) : Button(filename, reverseX, x, y, -1, action)
    {
    }
    ~Button()
    {
        UnloadTexture(normal);
        UnloadTexture(pressed);

        for (int i = buttons.size() - 1; i >= 0; i--)
        {
            if (buttons.at(i) == this)
            {
                buttons.erase(buttons.begin() + i);
                break;
            }
        }
    }
    void Update()
    {
        if (callbackQueued)
        {
            callbackQueued = false;
            callback();
        }

        // Keybinding should work even if button is disabled
        if (!isPressed && (mappedKey != -1 && IsKeyDown(mappedKey)))
        {
            Press();
            pressedByKey = true;
        }
        if (isPressed && ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !pressedByKey) || (mappedKey != -1 && IsKeyUp(mappedKey) && pressedByKey)))
        {
            state = &normal;
            isPressed = false;
        }

        if (!enabled)
            return;

        Vector2 mousePos = GetMousePosition();
        if (!isPressed &&
            (mousePos.x > position.x && mousePos.x < position.x + normal.width * BUTTON_SCALE &&
            mousePos.y > position.y && mousePos.y < position.y + normal.height * BUTTON_SCALE &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            Press();
            pressedByKey = false;
        }
    }
    void Render()
    {
        if (enabled)
            DrawTextureEx(*state, position, 0, BUTTON_SCALE, WHITE);
    }

    void SetEnabled(bool en)
    {
        enabled = en;
    }
private:
    void Press()
    {
        state = &pressed;
        isPressed = true;
        callbackQueued = true;
    }

    Texture2D normal;
    Texture2D pressed;

    Texture2D* state;
    bool isPressed = false;
    bool pressedByKey = false;

    int mappedKey;

    Vector2 position;

    std::function<void(void)> callback;

    bool enabled = true;
    bool callbackQueued = false;
};