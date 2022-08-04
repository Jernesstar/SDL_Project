#include "Text.h"

namespace Saddle::UI {

Text::Text(const std::string& _text, TTF_Font* _font, uint8_t size, SDL_Color& _color, SDL_Renderer* renderer) 
    : UIElement(), text(_text)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    rect = text_surface->clip_rect;
    rect = {rect.x, rect.y, rect.w * size, rect.h * size};
    center = {rect.w / 2, rect.h / 2};

    SDL_FreeSurface(text_surface);
}

Text::Text(const std::string& _text, const std::string& font_path, uint8_t size, SDL_Color& _color, SDL_Renderer* renderer) 
    : UIElement(), text(_text)
{
    std::string path = "Sandbox/";
    path.append(font_path);
    
    TTF_Font* _font = TTF_OpenFont(path.c_str(), 10 * size);
    SDL_Surface* text_surface = TTF_RenderText_Solid(_font, _text.c_str(), _color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    rect = text_surface->clip_rect;
    rect = {rect.x, rect.y, (rect.w / 5) * size, (rect.h / 5) * size};
    center = {rect.w / 2, rect.h / 2};

    SDL_FreeSurface(text_surface);
    TTF_CloseFont(_font);
}

Text::~Text()
{
    UIElement::~UIElement();
}

}