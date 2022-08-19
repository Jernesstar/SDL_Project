#include "Input.h"

#include <SDL.h>

namespace Saddle {

bool Input::IsKeyPressed(KeyCode key)
{
    SDL_PumpEvents();
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);

    // Special cases
    if(key == Key::Ctrl) return keyboard_state[Key::LeftCtrl] || keyboard_state[Key::RightCtrl];
    if(key == Key::Shift) return keyboard_state[Key::LeftShift] || keyboard_state[Key::RightShift];
    if(key == Key::Alt) return keyboard_state[Key::LeftAlt] || keyboard_state[Key::RightAlt];

    return keyboard_state[key]; // Will return 1 if key was pressed, 0 otherwise
}

bool Input::AreKeysPressed(KeyCode key1, KeyCode key2)
{
    if(IsKeyPressed(key1))
    {
        if(IsKeyPressed(key2)) return true;
    }
    return false;
}

bool Input::AreKeysPressed(KeyCode key1, KeyCode key2, KeyCode key3)
{
    if(AreKeysPressed(key1, key2))
    {
        if(IsKeyPressed(key3)) return true;
    }
    return false;
}

bool Input::AreKeysPressed(KeyCode key1, KeyCode key2, KeyCode key3, KeyCode key4)
{
    if(AreKeysPressed(key1, key2, key3))
    {
        if(IsKeyPressed(key4)) return true;
    }
    return false;
}

bool Input::IsMouseButtonPressed(MouseCode mouse_button)
{
    SDL_PumpEvents();
    int button_mask = SDL_GetMouseState(nullptr, nullptr); // Mask representing what mouse button is currently pressed
    return button_mask & SDL_BUTTON(mouse_button); // Return 1 if mouse_button is pressed, else 0
}

MousePosition Input::GetMousePosition()
{
    SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);
    return {x, y};
}

int Input::GetMouseX()
{
    return GetMousePosition().x;
}

int Input::GetMouseY()
{
    return GetMousePosition().y;
}

}