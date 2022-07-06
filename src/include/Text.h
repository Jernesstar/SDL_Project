#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "UI_Element.h"

class Text : public UI_Element {

public:
    const std::string text;

    Text(std::string _text, int size, TTF_Font* _font, SDL_Color color, SDL_Renderer* renderer);
    ~Text();

private:
    SDL_Point center;
};