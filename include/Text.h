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

    SDL_Texture** GetTexture();
    SDL_Rect* GetRect();

private:
    SDL_Point center;
};