#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Audio.h"

namespace Saddle {
    
struct IComponent {
protected:
    IComponent() = default;
    ~IComponent() = default;
};

struct RectComponent : public IComponent {
    Uint32 width, height;  

    RectComponent(Uint32 w = 1, Uint32 h = 1) : width(w), height(h) { }
    RectComponent(const RectComponent& other) : width(other.width), height(other.height) { }
};

struct Coordinate2DComponent : public IComponent {
    Uint32 x, y;

    Coordinate2DComponent(int x = 0, int y = 0) : x(x), y(y) { }
    Coordinate2DComponent(const Coordinate2DComponent& other) : x(other.x), y(other.y) { }
};

struct TextureComponent : public IComponent {
    SDL_Texture* texture;

    TextureComponent() = default;
    ~TextureComponent() { if(texture) SDL_DestroyTexture(texture); }
};

struct RGBColorComponent : public IComponent {
    Uint8 r, g, b;

    RGBColorComponent() = default;
    RGBColorComponent(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) { }
    RGBColorComponent(const RGBColorComponent& other) : r(other.r), g(other.g), b(other.b) { }
};

struct SoundComponent : public IComponent {
    Mix_Chunk* Sound;
    Uint8 Volume;
    
    SoundComponent(const std::string& file_path)
        : IComponent(), Sound(Mix_LoadWAV(file_path.c_str())), Volume(AUDIO_MAX_VOLUME) { }
    ~SoundComponent() { if(Sound) Mix_FreeChunk(Sound); }
};

}