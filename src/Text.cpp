#include "Text.h"

Text::Text(std::string _text, int size, TTF_Font* _font, SDL_Color _color, SDL_Renderer* renderer) 
: text(_text)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(_font, const_cast<char*>(_text.c_str()), _color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    rect = text_surface->clip_rect;
    rect = {rect.x, rect.y, rect.w * size, rect.h * size};
    center = {rect.w / 2, rect.h / 2};

    SDL_FreeSurface(text_surface);
}

Text::~Text()
{
    if(texture)
        SDL_DestroyTexture(texture);
}