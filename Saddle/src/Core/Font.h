#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Components.h"

namespace Saddle {
class Font { 
public:
    const int Size;

public:
    Font(const std::string& font_path, int size)
        : Size(size)
    {
        m_Font = TTF_OpenFont(font_path.c_str(), size);
    }

    ~Font()
    {
        TTF_CloseFont(m_Font);
    }	

    TTF_Font* GetFont() { return m_Font; }

    SDL_Surface* GetSurfaceFromText(const std::string& text, RGBColorComponent& color)
    {
        SDL_Color _color = { color.r, color.g, color.b };
        return TTF_RenderText_Solid(m_Font, text.c_str(), _color); 
    }

private:
    TTF_Font* m_Font;
};

}
