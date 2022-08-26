#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Saddle/Scene/Components.h"

namespace Saddle {
    
class Font { 
public:
    const int Size;

public:
    Font(const std::string& font_path, int size);
    ~Font();

    TTF_Font* GetFont();
    SDL_Surface* GetSurfaceFromText(const std::string& text, RGBColorComponent& color);

private:
    TTF_Font* m_Font;
};

}
