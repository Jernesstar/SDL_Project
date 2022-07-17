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

    public:
        Text() { }
        Text(const std::string& _text, uint8_t size, TTF_Font*& _font, SDL_Color& _color, SDL_Renderer*& renderer);
        ~Text();
    };
        
}