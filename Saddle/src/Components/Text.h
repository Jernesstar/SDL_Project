#pragma once

#include "UIElement.h"

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

namespace Saddle {

namespace UI { 

/// Class that is used to abstract text rendering
class Text : public UIElement {

public:
    const std::string text;

public:
    Text() { }
    Text(const std::string& _text, TTF_Font* _font, uint8_t size, SDL_Color& _color, SDL_Renderer* renderer);
    Text(const std::string& _text, const std::string& font_path, uint8_t size, SDL_Color& _color, SDL_Renderer* renderer);
    ~Text();
};
        
}

}