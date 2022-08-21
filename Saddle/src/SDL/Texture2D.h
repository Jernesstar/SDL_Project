#pragma once

#include <SDL.h>

namespace Saddle {

class Texture2D {
public:
    Texture2D() = default;
    // Note: Maybe abstract SDL_Surface
    Texture2D(SDL_Surface* surface);
    ~Texture2D();

private:
    int m_Width, m_Height;
    SDL_Texture* m_Texture = nullptr;

    friend class Renderer;
    friend class TextureSystem;
};

}