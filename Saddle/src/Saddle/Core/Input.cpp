#include "Input.h"

#include <SDL.h>

namespace Saddle {

bool Input::KeyPressed(KeyCode key)
{
    SDL_PumpEvents();
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);

    // Special cases
    if(key == Key::Ctrl) return keyboard_state[Key::LeftCtrl] || keyboard_state[Key::RightCtrl];
    if(key == Key::Shift) return keyboard_state[Key::LeftShift] || keyboard_state[Key::RightShift];
    if(key == Key::Alt) return keyboard_state[Key::LeftAlt] || keyboard_state[Key::RightAlt];

    return keyboard_state[key]; // Will return 1 if key was pressed, 0 otherwise
}

bool Input::KeysPressed(KeyCode key1, KeyCode key2)
{
    if(KeyPressed(key1))
    {
        if(KeyPressed(key2)) return true;
    }
    return false;
}

bool Input::KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3)
{
    if(KeysPressed(key1, key2))
    {
        if(KeyPressed(key3)) return true;
    }
    return false;
}

bool Input::KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3, KeyCode key4)
{
    if(KeysPressed(key1, key2, key3))
    {
        if(KeyPressed(key4)) return true;
    }
    return false;
}

bool Input::MouseButtonPressed(MouseCode mouse_button)
{
    SDL_PumpEvents();
    int button_mask = SDL_GetMouseState(nullptr, nullptr); // Mask representing what mouse button is currently pressed
    return button_mask & SDL_BUTTON(mouse_button); // Return 1 if mouse_button is pressed, else 0
}

bool Input::MousePressedOn(const Rect& rect, const Transform& transform)
{
    // Check if the mouse clicked within the rectangle
    auto& coordinate = transform.Coordinate;
    auto [mouse_x, mouse_y] = Input::GetMousePosition();
    bool x_coordinate_is_in_bound = coordinate.x <= mouse_x && mouse_x <= coordinate.x + rect.Width;
    bool y_coordinate_is_in_bound = coordinate.y <= mouse_y && mouse_y <= coordinate.y + rect.Height;

    return x_coordinate_is_in_bound && y_coordinate_is_in_bound;
}

Vector2D Input::GetMousePosition()
{
    SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);
    return { (float)x, (float)y};
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