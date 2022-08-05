#include "Components.h"
#include "Font.h"

#include "Application.h"

namespace Saddle {

TextComponent::TextComponent(const std::string& _text, Font font, SDL_Color& _color) 
    : IComponent(), text(_text)
{
    SDL_Surface* text_surface = font.GetSurfaceFromText(_text, _color);
    texture_component.texture = SDL_CreateTextureFromSurface(Application::Get().GetWindow().GetRenderer(), text_surface);
    
    auto clip_rect = text_surface->clip_rect;
    rect = { rect.width * font.Size, rect.height * font.Size };
    center = { rect.width / 2, rect.height / 2 };

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