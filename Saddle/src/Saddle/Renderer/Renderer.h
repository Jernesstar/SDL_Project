#pragma once

#include <SDL.h>

#include "SDL/Coordinate2D.h"
#include "SDL/Rect.h"
#include "SDL/Texture2D.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void DrawTexture(Texture2D texture, Coordinate2D coordinate, Rect rect);
    static void SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color);
    static void Render();

private:
    inline static SDL_Renderer* s_Renderer;

    Renderer() = delete;
    ~Renderer() = delete;
};

}