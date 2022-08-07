#include "Entity.h"
#include "Components.h"
#include "Font.h"

#include "Application.h"

namespace Saddle {

class Text {

public:
    static void CreateText(Entity& entity, const std::string& text, Font& font, RGBColorComponent& color)
    {
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
        RectComponent& rect_component = entity.GetComponent<RectComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* text_surface = font.GetSurfaceFromText(text, color);
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);

        auto clip_rect = text_surface->clip_rect;
        rect_component = { (Uint32)clip_rect.w, (Uint32)clip_rect.h };
    }

private:
    Text() = delete;
    ~Text() = delete;
};

}