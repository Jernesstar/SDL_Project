#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Audio.h"
#include "Font.h"

namespace Saddle {
struct IComponent {
protected:
    IComponent() = default;
    ~IComponent() = default;
};

struct RectComponent : public IComponent {
    Uint32 width, height;  

    RectComponent() = default;
    RectComponent(Uint32 w, Uint32 h) : width(w), height(h) { }
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
    ~TextureComponent() { SDL_DestroyTexture(texture); };
};

struct RGBColorComponent : public IComponent {
    uint8_t r, g, b;

    RGBColorComponent() = default;
    RGBColorComponent(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) { }
    RGBColorComponent(const RGBColorComponent& other) : r(other.r), g(other.g), b(other.b) { }
};

struct SoundComponent : public IComponent {
    SoundComponent(const std::string& file_path);
    ~SoundComponent() { if(m_Sound) Mix_FreeChunk(m_Sound); }

    Mix_Chunk* GetSound() { return m_Sound; }

    void Play(int loops = 0, int channel = -1);
    void SetVolume(Uint8 volume);
    void IncreaseVolume(Uint8 delta) { SetVolume(m_Volume + delta); }
    void DecreaseVolume(Uint8 delta) { SetVolume(m_Volume - delta); }

private:
    Mix_Chunk* m_Sound;
    Uint8 m_Volume;
};

struct TextComponent : public IComponent {
    const std::string text;
    TextureComponent texture_component; 
    RectComponent rect_component;
    Coordinate2DComponent coordinate2D_component;
    Coordinate2DComponent center;

    TextComponent() = default;
    TextComponent(const std::string& _text, Font font, RGBColorComponent _color);
    TextComponent(const std::string& _text, const std::string& font_path, int font_size, RGBColorComponent color);
    ~TextComponent();
};

}