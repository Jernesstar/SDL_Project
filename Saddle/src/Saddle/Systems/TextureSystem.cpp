#include "TextureSystem.h"

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Scene/Components.h"
#include "Saddle/Renderer/Renderer.h"

namespace Saddle {

void TextureSystem::CreateText(Entity& entity, const std::string& text, Font& font)
{
    auto renderer = Application::Get().GetWindow().GetRenderer();
    RectComponent& rect_component = entity.GetComponent<RectComponent>();
    RGBColorComponent& color_component = entity.GetComponent<RGBColorComponent>();
    TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
    TransformComponent& transform_component = entity.GetComponent<TransformComponent>();

    SDL_Surface* text_surface = font.GetSurfaceFromText(text, color_component);
    texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    auto rect = text_surface->clip_rect;
    
    texture_component.Texture.Width = rect.w * transform_component.Scale.x;
    texture_component.Texture.Height = rect.h * transform_component.Scale.y;
    rect_component = { (float)rect.w * transform_component.Scale.x, 
        (float)rect.h * transform_component.Scale.y };

    SDL_FreeSurface(text_surface);
}

void TextureSystem::CreateRectangle(Entity& entity, int width, int height, int depth, 
    int r_mask, int g_mask, int b_mask, int a_mask)
{
    auto renderer = Application::Get().GetWindow().GetRenderer();
    RectComponent& rect_component = entity.GetComponent<RectComponent>();
    RGBColorComponent& color = entity.GetComponent<RGBColorComponent>();
    TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
    TransformComponent& transform_component = entity.GetComponent<TransformComponent>();

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
    texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto rect = surface->clip_rect;
    texture_component.Texture.Width = rect.w * transform_component.Scale.x;
    texture_component.Texture.Height = rect.h * transform_component.Scale.y;
    rect_component = { (float)rect.w * transform_component.Scale.x, 
        (float)rect.h * transform_component.Scale.y };

    
    SADDLE_CORE_ASSERT(texture_component.Texture.m_Texture != nullptr, "Could not create texture");
}

void TextureSystem::CreateCircle(Entity& entity, int radius)
{
    auto renderer = Application::Get().GetWindow().GetRenderer();
    RGBColorComponent& color = entity.GetComponent<RGBColorComponent>();
    TextureComponent& texture_component = entity.GetComponent<TextureComponent>();

    int flags = 0;
    int depth = 32;
    int _radius = (int)radius;

    SDL_Surface* surface = SDL_CreateRGBSurface(flags, 2 * _radius, 2 * _radius, depth, 0, 0, 0, 0);
    
    int dx, dy;
    SDL_LockSurface(surface);
    for(int w = 0; w < surface->w; w++)
    {
        for(int h = 0; h < surface->h; h++)
        {
            dx = _radius - w; // horizontal offset
            dy = _radius - h; // vertical offset
            if((dx * dx + dy * dy) <= (_radius * _radius))
            {
                Renderer::SetPixel(surface, (surface->w * 0.5) + dx, (surface->h * 0.5) + dy, color);
            }
        }
    }
    SDL_UnlockSurface(surface);

    texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

}