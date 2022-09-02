#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "SDL/RGBColor.h"

namespace Saddle {
    
class Font { 
public:
    const int Size;

public:
    Font(const std::string& font_path, int size);
    ~Font();

    TTF_Font* GetFont();
    SDL_Surface* GetSurfaceFromText(const std::string& text, const RGBColor& color);

private:
    TTF_Font* m_Font;
};

}
