#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "UI_Element.h"

class Text : public UI_Element {

public:
    const std::string text;

    Text(std::string _text, uint8_t size, TTF_Font*& _font, SDL_Color& _color, SDL_Renderer*& renderer);
    ~Text();
    
    void Scale(int8_t scalar);
    void Translate(int8_t delta_x, int8_t delta_y);
    void PlaceAt(uint16_t _x, uint16_t _y);

    SDL_Texture** GetTexture();
    SDL_Rect* GetRect();
};