#include "Input.h"

#include <SDL.h>

namespace Saddle {

bool Input::IsKeyPressed(Key key)
{
    SDL_PumpEvents();
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
    return keyboard_state[key]; // Will return 1 if key was pressed, 0 otherwise
}

bool Input::IsMouseButtonPressed(Mouse mouse_button)
{
    SDL_PumpEvents();
    int button_mask = SDL_GetMouseState(nullptr, nullptr); // Mask representing what mouse button is pressed
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