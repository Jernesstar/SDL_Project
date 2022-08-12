#include "Input.h"

#include <SDL.h>

namespace Saddle {

bool Input::IsKeyPressed(Key key)
{
    SDL_PumpEvents();
    const Uint8* key_state = SDL_GetKeyboardState(nullptr);
    return key_state[key]; // Will return 1 if key was pressed, 0 otherwise
}

bool Input::IsMouseButtonPressed(Mouse mouse_button)
{
    SDL_PumpEvents();
    int button_mask = SDL_GetMouseState(nullptr, nullptr);
    return button_mask & SDL_BUTTON(mouse_button);
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