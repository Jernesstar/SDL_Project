#pragma once

#include <iostream>
#include <functional>
#include <cmath>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Audio.h"
#include "KeyEvents.h"
#include "MouseEvents.h"

namespace Saddle {
    
struct IComponent {
protected:
    IComponent() = default;
    ~IComponent() = default;
};

struct Coordinate2DComponent : public IComponent {
    Uint32 x, y;

    Coordinate2DComponent(int x = 0, int y = 0) : x(x), y(y) { }
    Coordinate2DComponent(const Coordinate2DComponent& other) : x(other.x), y(other.y) { }
};

struct EventListenerComponent : public IComponent {
    std::function<void(KeyPressedEvent& event)> KeyPressedEvent;
    std::function<void(KeyReleasedEvent& event)> KeyReleasedEvent;
    std::function<void(MouseMovedEvent& event)> MouseMovedEvent;
    std::function<void(MouseScrolledEvent& event)> MouseScrolledEvent;
    std::function<void(MouseButtonPressedEvent& event)> MouseButtonPressedEvent;
    std::function<void(MouseButtonReleasedEvent& event)> MouseButtonReleasedEvent;

    EventListenerComponent() = default;
    EventListenerComponent(const EventListenerComponent& other) = default;
};

struct PhysicsBodyComponent : public IComponent {
    float Speed;
    float VelocityX;
    float VelocityY;
    float Bounciness;

    PhysicsBodyComponent(float velocity_x = 0.0f, float velocity_y = 0.0f, float bounciness = 0.0f) 
        : VelocityX(velocity_x), VelocityY(velocity_y), Bounciness(bounciness)
    {
        // Distance formula + speed formula: sqrt(a^2 + b^2) / time
        Speed = pow((VelocityX * VelocityX) + (VelocityY * VelocityY), 0.5) / 1;
    }
};

struct RectComponent : public IComponent {
    Uint32 Width, Height;  

    RectComponent(Uint32 w = 1, Uint32 h = 1) : Width(w), Height(h) { }
    RectComponent(const RectComponent& other) : Width(other.Width), Height(other.Height) { }
};

struct RGBColorComponent : public IComponent {
    Uint8 r, g, b;

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

struct TextureComponent : public IComponent {
    SDL_Texture* texture;

    TextureComponent() = default;
    ~TextureComponent() { if(texture) SDL_DestroyTexture(texture); }
};

}