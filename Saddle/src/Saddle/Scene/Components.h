#pragma once

#include <functional>
#include <cmath>

#include "SDL/Sound.h"
#include "SDL/Texture2D.h"
#include "SDL/Audio.h"
#include "Saddle/Events/KeyEvents.h"
#include "Saddle/Events/MouseEvents.h"
#include "Saddle/Events/WindowEvents.h"

namespace Saddle {
    
struct IComponent {
protected:
    ~IComponent() = default;
    IComponent() = default;
};

struct Coordinate2DComponent : public IComponent {
    float x, y;

    Coordinate2DComponent(float x = 0, float y = 0) : x(x), y(y) { }
};

struct EventListenerComponent : public IComponent {
    std::function<void(KeyPressedEvent& event)> OnKeyPressed;
    std::function<void(KeyReleasedEvent& event)> OnKeyReleased;
    std::function<void(MouseMovedEvent& event)> OnMouseMoved;
    std::function<void(MouseScrolledEvent& event)> OnMouseScrolled;
    std::function<void(MouseButtonPressedEvent& event)> OnMouseButtonPressed;
    std::function<void(MouseButtonReleasedEvent& event)> OnMouseButtonReleased;
    std::function<void(WindowResizedEvent& event)> OnWindowResized;
    std::function<void(WindowClosedEvent& event)> OnWindowClosed;

    EventListenerComponent() = default;
    EventListenerComponent(const EventListenerComponent& other) = default;
    ~EventListenerComponent() = default;
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
    float Width, Height;

    RectComponent(float width = 1, float height = 1) : Width(width), Height(height) { }
};

struct RGBColorComponent : public IComponent {
    Uint8 r, g, b;

    RGBColorComponent(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) { }
    RGBColorComponent(const RGBColorComponent& other) : r(other.r), g(other.g), b(other.b) { }
};

struct SoundComponent : public IComponent {
    Sound Sound;
    
    SoundComponent(const std::string& file_path) : IComponent(), Sound(file_path) { }
    ~SoundComponent() = default;
};

struct TextureComponent : public IComponent {
    Texture2D Texture;

    TextureComponent() = default;
    ~TextureComponent() = default;
};

}