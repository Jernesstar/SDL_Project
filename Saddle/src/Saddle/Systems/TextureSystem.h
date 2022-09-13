#pragma once

#include "SDL/Font.h"
#include "Saddle/Scene/Entity.h"

namespace Saddle {

struct TextureSystemDependencies {
    SDL_Renderer* renderer;
    RGBColorComponent* color_component;
    TextureComponent* texture_component;
    TransformComponent* transform_component;
};

class TextureSystem {
public:
    static void CreateText(Entity& entity, const std::string& text, Font& font);
    static void CreateRectangle(Entity& entity, int width, int height, int depth = 32, 
        int r_mask = 0, int g_mask = 0, int b_mask = 0, int a_mask = 0);
    static void CreateCircle(Entity& entity, int radius);

    static bool HasDependencies(Entity& entity)
    {
        return entity.HasComponent<RGBColorComponent>() && entity.HasComponent<TextureComponent>()
            && entity.HasComponent<TransformComponent>();
    }

private:
    TextureSystem() = delete;
    ~TextureSystem() = delete;

    static TextureSystemDependencies GetDependencies(Entity& entity)
    {
        return { Application::Get().GetWindow().GetRenderer(), 
            &entity.GetComponent<RGBColorComponent>(), &entity.GetComponent<TextureComponent>(),
            &entity.GetComponent<TransformComponent>()
        };
    }
};

}