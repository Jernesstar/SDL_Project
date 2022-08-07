#include "Entity.h"
#include "Components.h"
#include "Font.h"

#include "Application.h"

namespace Saddle {

class Text {

public:
    static void CreateText(Entity& entity, const std::string& text, Font font, RGBColorComponent color)
    {
        auto texture_component = entity.GetComponent<TextureComponent>();
        auto rect_component = entity.GetComponent<RectComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* text_surface = font.GetSurfaceFromText(text, color);
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);

        auto clip_rect = text_surface->clip_rect;
        rect_component = { clip_rect.w, clip_rect.h };
        rect_component.Scale(font.Size);
    }

private:
    Text() = delete;
    ~Text() = delete;
};

}