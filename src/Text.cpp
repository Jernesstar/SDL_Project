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

void Text::Scale(int8_t scalar)
{
    UIElement::Scale(scalar);
}

void Text::Translate(int8_t delta_x, int8_t delta_y)
{
    UIElement::Translate(delta_x, delta_y);
}

void Text::PlaceAt(uint16_t _x, uint16_t _y)
{
    UIElement::PlaceAt(_x, _y);
}

SDL_Rect* Text::GetRect()
{
    return UIElement::GetRect();
}

SDL_Texture** Text::GetTexture()
{
    return UIElement::GetTexture();
}

SDL_Point* Text::GetCenter()
{
    return UIElement::GetCenter();
}

}