#include "Font.h"

namespace Saddle {

Font::Font(const std::string& font_path, int size) : Size(size)
{
    m_Font = TTF_OpenFont(font_path.c_str(), size);
}

Font::~Font() { TTF_CloseFont(m_Font); }	

TTF_Font* Font::GetFont() { return m_Font; }

SDL_Surface* Font::GetSurfaceFromText(const std::string& text, const RGBColor& color)
{
    SDL_Color _color = { color.r, color.g, color.b };
    return TTF_RenderText_Solid(m_Font, text.c_str(), _color); 
}

}