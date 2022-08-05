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
    int width, height;  

    RectComponent() = default;
    RectComponent(int w, int h) : width(w), height(h) {}
    void Scale(int32_t scalar)
    {  
        width *= scalar;
        height *= scalar;
    }
};

struct Coordinate2DComponent : public IComponent {
    int x, y;

    Coordinate2DComponent() = default;
    Coordinate2DComponent(int x, int y) : x(x), y(y) {}

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

struct SoundComponent : public IComponent {
    SoundComponent(const std::string& file_path);
    ~SoundComponent();

    Mix_Chunk* GetSound();

    void Play(int loops = 0, int channel = -1);
    void SetVolume(Uint8 volume);
    void IncreaseVolume(Uint8 delta);
    void DecreaseVolume(Uint8 delta);

private:
    Mix_Chunk* m_Sound;
    Uint8 m_Volume;
};

struct TextureComponent : public IComponent {
    SDL_Texture* texture;

    TextureComponent() = default;
    ~TextureComponent() { SDL_DestroyTexture(texture); };
};

struct TextComponent : public IComponent {
    const std::string text;
    TextureComponent texture_component; 
    RectComponent rect_component;
    Coordinate2DComponent coordinate2D_component;
    Coordinate2DComponent center;

    TextComponent() = default;
    TextComponent(const std::string& _text, Font font, SDL_Color& _color);
    TextComponent(const std::string& _text, const std::string& font_path, int font_size, SDL_Color& color);
    ~TextComponent();
};

}