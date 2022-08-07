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
    
    void Scale(int32_t scalar)
    {  
        width *= scalar;
        height *= scalar;
    }
};

struct Coordinate2DComponent : public IComponent {
    Uint32 x, y;

    Coordinate2DComponent(int x = 0, int y = 0) : x(x), y(y) { }

    void Translate(int32_t delta_x, int32_t delta_y) 
    { 
        x += delta_x;
        y += delta_y;
    }
    void PlaceAt(uint32_t _x, uint32_t _y)
    {
        x = _x;
        y = _y;
    }
};

struct TextureComponent : public IComponent {
    SDL_Texture* texture;

    TextureComponent() = default;
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
        : IComponent()
    {
        Sound = Mix_LoadWAV(file_path.c_str());
        Volume = AUDIO_MAX_VOLUME;
    }
    ~SoundComponent() { if(Sound) Mix_FreeChunk(Sound); }

    Mix_Chunk* GetSound() { return Sound; }
    void Play(int loops = 0, int channel = -1)
    {
        // loops = 0: Play the sound once
        // channel = -1: First available sound channel
        Mix_PlayChannel(channel, Sound, loops);
    }
    void SetVolume(Uint8 volume)
    {
        Volume = volume;
        if(volume > AUDIO_MAX_VOLUME)
            Volume = AUDIO_MAX_VOLUME;
        else if(volume < AUDIO_MIN_VOLUME)
            Volume = AUDIO_MIN_VOLUME;
        
        Mix_VolumeChunk(Sound, Volume);
    }
    void IncreaseVolume(Uint8 delta) { SetVolume(Volume + delta); }
    void DecreaseVolume(Uint8 delta) { SetVolume(Volume - delta); }
};

}