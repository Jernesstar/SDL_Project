#include "Components.h"
#include "Font.h"

#include "Application.h"

namespace Saddle {

TextComponent::TextComponent(const std::string& _text, Font font, SDL_Color& _color) 
    : IComponent(), text(_text)
{
    SDL_Surface* text_surface = font.GetSurfaceFromText(_text, _color);
    auto renderer = Application::Get().GetWindow().GetRenderer();
    texture_component.texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    auto clip_rect = text_surface->clip_rect;
    rect_component = { rect_component.width * font.Size, rect_component.height * font.Size };
    center = { rect_component.width / 2, rect_component.height / 2 };

    SDL_FreeSurface(text_surface);
}

TextComponent::TextComponent(const std::string& _text, const std::string& font_path, int font_size, SDL_Color& color) 
    : text(_text)
{    
    Font font(font_path, font_size);
    TextComponent(_text, font, color);
}

TextComponent::~TextComponent() { }

}