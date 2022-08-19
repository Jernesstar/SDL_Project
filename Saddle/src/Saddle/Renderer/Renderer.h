#pragma once

#include <SDL.h>

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void DrawTexture(SDL_Rect& rect, SDL_Texture* texture);
    static void SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color);
    static void Render();

private:
    inline static SDL_Renderer* s_Renderer;

    Renderer() = delete;
    ~Renderer() = delete;
};

}