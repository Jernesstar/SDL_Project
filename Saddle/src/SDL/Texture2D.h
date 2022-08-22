#pragma once

#include <SDL.h>

namespace Saddle {

class Texture2D {
public:
    int Width = 0, Height = 0;
    
public:
    Texture2D() = default;
    // Note: Maybe abstract SDL_Surface
    Texture2D(SDL_Surface* surface);
    Texture2D(Texture2D&& other);
    Texture2D(const Texture2D& other) = delete;
    ~Texture2D();

    Texture2D& operator=(Texture2D&& other);
    Texture2D& operator=(const Texture2D& other) = delete;

private:
    SDL_Texture* m_Texture;
    
    friend class Image;
    friend class Renderer;
    friend class TextureSystem;
};

}