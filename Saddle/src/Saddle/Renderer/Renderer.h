#pragma once

#include <SDL.h>

#include "SDL/Texture2D.h"
#include "SDL/Transform.h"
#include "SDL/RGBColor.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear();
    static void DrawTexture(const Texture2D& texture, const Transform& transform);
    static void Render();
    static void SetPixel(SDL_Surface* surface, int x, int y, RGBColor color);

private:
    inline static SDL_Renderer* s_Renderer;

    Renderer() = delete;
    ~Renderer() = delete;
};

}