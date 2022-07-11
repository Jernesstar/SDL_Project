#pragma once

#include "GameObject.h"

#include <SDL.h>

namespace UI {
class UIElement : public GameObject {

public:
    void Scale(int32_t scalar);
    void Translate(int32_t delta_x, int32_t delta_y);
    void PlaceAt(uint32_t _x, uint32_t _y);
    
    SDL_Rect* GetRect();
    SDL_Texture** GetTexture();
    SDL_Point* GetCenter();

protected:
    UIElement();
    ~UIElement();
};

}