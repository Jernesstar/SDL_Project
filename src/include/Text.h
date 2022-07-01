#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

class Text {
public:
    const std::string text;
    SDL_Texture* texture;
    SDL_Rect rect;

    SDL_Point center;

    Text(std::string _text, int size, TTF_Font* _font, SDL_Color color, SDL_Renderer* renderer);
    ~Text();
};