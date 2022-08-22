#pragma once

#include "SDL/Font.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Scene/Components.h"
#include "Saddle/Scene/Entity.h"
#include "Saddle/Renderer/Renderer.h"

namespace Saddle {

class TextureSystem {
public:
    static void CreateText(Entity& entity, const std::string& text, Font& font)
    {
        auto renderer = Application::Get().GetWindow().GetRenderer();
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
        RectComponent& rect_component = entity.GetComponent<RectComponent>();
        RGBColorComponent& color_component = entity.GetComponent<RGBColorComponent>();

        SDL_Surface* text_surface = font.GetSurfaceFromText(text, color_component);
        texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        auto clip_rect = text_surface->clip_rect;
        
        texture_component.Texture.Width = clip_rect.w;
        texture_component.Texture.Height = clip_rect.h;
        rect_component = { clip_rect.w, clip_rect.h };
        
        SDL_FreeSurface(text_surface);
    }

    static void CreateRectangle(Entity& entity, int width, int height, int depth = 32, 
        int r_mask = 0, int g_mask = 0, int b_mask = 0, int a_mask = 0)
    {
        auto renderer = Application::Get().GetWindow().GetRenderer();
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
        RGBColorComponent& color = entity.GetComponent<RGBColorComponent>();

        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask);
        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
        texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);

        auto rect = surface->clip_rect;
        texture_component.Texture.Width = rect.w;
        texture_component.Texture.Height = rect.h;
        
        SADDLE_CORE_ASSERT(texture_component.Texture.m_Texture != nullptr, "Could not create texture");
    }

    static void CreateCircle(Entity& entity, int radius)
    {
        auto renderer = Application::Get().GetWindow().GetRenderer();
        RGBColorComponent& color = entity.GetComponent<RGBColorComponent>();
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();

        int flags = 0;
        int depth = 32;
        int _radius = (int)radius;

        SDL_Surface* surface = SDL_CreateRGBSurface(flags, 2 * _radius, 2 * _radius, depth, 0, 0, 0, 0);
        SDL_Color _color = {color.r, color.g, color.b};
        
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
                    Renderer::SetPixel(surface, (surface->w * 0.5) + dx, (surface->h * 0.5) + dy, _color);
                }
            }
        }
        SDL_UnlockSurface(surface);

        texture_component.Texture.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
};

}