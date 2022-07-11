#pragma once

#include "UIElement.h"

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

namespace UI {
    
/// Class that is used to abstract text rendering
class Text : public UIElement {

public:
    const std::string text;

    Text(std::string _text, uint8_t size, TTF_Font*& _font, SDL_Color& _color, SDL_Renderer*& renderer);
    ~Text();
    
    void Scale(int8_t scalar);
    void Translate(int8_t delta_x, int8_t delta_y);
    void PlaceAt(uint16_t _x, uint16_t _y);

    SDL_Rect* GetRect();
    SDL_Texture** GetTexture();
    SDL_Point* GetCenter();
};
    
}