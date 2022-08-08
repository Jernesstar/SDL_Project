#pragma once

#include "Entity.h"
#include "Components.h"
#include "Font.h"

#include "Application.h"

namespace Saddle {

class TextureSystem {

public:
    static void CreateText(Entity& entity, const std::string& text, Font& font)
    {
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
        RectComponent& rect_component = entity.GetComponent<RectComponent>();
        RGBColorComponent& color_component = entity.GetComponent<RGBColorComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* text_surface = font.GetSurfaceFromText(text, color_component);
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);

        auto clip_rect = text_surface->clip_rect;
        rect_component = { (Uint32)clip_rect.w, (Uint32)clip_rect.h };
    }

    static void CreateRectangle(Entity& entity, int width, int height, int depth = 32, 
        int r_mask = 0, int g_mask = 0, int b_mask = 0, int a_mask = 0)
    {
        TextureComponent& texture_component = entity.GetComponent<TextureComponent>();
        RGBColorComponent& color = entity.GetComponent<RGBColorComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r, color.g, color.b));
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    static void CreateText(Entity* entity, const std::string& text, Font& font)
    {
        TextureComponent& texture_component = entity->GetComponent<TextureComponent>();
        RectComponent& rect_component = entity->GetComponent<RectComponent>();
        RGBColorComponent& color = entity->GetComponent<RGBColorComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* text_surface = font.GetSurfaceFromText(text, color);
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_FreeSurface(text_surface);

        auto clip_rect = text_surface->clip_rect;
        rect_component = { (Uint32)clip_rect.w, (Uint32)clip_rect.h };
    }

    static void CreateRectangle(Entity* entity, int width, int height, int depth = 32, 
        int r_mask = 0, int g_mask = 0, int b_mask = 0, int a_mask = 0)
    {
        TextureComponent& texture_component = entity->GetComponent<TextureComponent>();
        RGBColorComponent& color = entity->GetComponent<RGBColorComponent>();
        auto renderer = Application::Get().GetWindow().GetRenderer();

        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, r_mask, g_mask, b_mask, a_mask);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r, color.g, color.b));
        texture_component.texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

};

}