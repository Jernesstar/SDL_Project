#include "Text.h"

namespace UI {

    Text::Text(std::string _text, uint8_t size, TTF_Font*& _font, SDL_Color& _color, SDL_Renderer*& renderer) : 
    UIElement(), text(_text)
    {
        SDL_Surface* text_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        
        rect = text_surface->clip_rect;
        rect = {rect.x, rect.y, rect.w * size, rect.h * size};
        center = {rect.w / 2, rect.h / 2};

        SDL_FreeSurface(text_surface);
    }

    Text::~Text()
    {
        UIElement::~UIElement();
    }

}