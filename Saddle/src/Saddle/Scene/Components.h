#pragma once

#include <functional>

#include "SDL/Audio.h"
#include "SDL/Sound.h"
#include "SDL/Texture2D.h"
#include "Saddle/Events/KeyEvents.h"
#include "Saddle/Events/MouseEvents.h"
#include "Saddle/Core/Vector.h"
#include "Saddle/Events/WindowEvents.h"

namespace Saddle {
    
struct IComponent {
protected:
    ~IComponent() = default;
    IComponent() = default;
};

struct EventListenerComponent : public IComponent {
    template<typename TEvent>
    using Callback = std::function<void(TEvent&)>;

    Callback<KeyPressedEvent>          OnKeyPressed;
    Callback<KeyReleasedEvent>         OnKeyReleased;
    Callback<MouseMovedEvent>          OnMouseMoved;
    Callback<MouseScrolledEvent>       OnMouseScrolled;
    Callback<MouseButtonPressedEvent>  OnMouseButtonPressed;
    Callback<MouseButtonReleasedEvent> OnMouseButtonReleased;
    Callback<WindowResizedEvent>       OnWindowResized;
    Callback<WindowClosedEvent>        OnWindowClosed;

    EventListenerComponent() = default;
};

struct RectComponent : public IComponent {
    float Width, Height;

    RectComponent(float width = 1, float height = 1) : Width(width), Height(height) { }
};

struct RigidBodyComponent : public IComponent {
    Vector2D Velocity;
    float Speed, RotationSpeed, Bounciness;

    RigidBodyComponent(const Vector2D& velocity = Vector2D(), float rotation_speed = 0.0f, float bounciness = 0.0f) 
        : RotationSpeed(rotation_speed), Bounciness(bounciness) { Speed = Magnitude(Velocity); }
};

struct RGBColorComponent : public IComponent {
    Uint8 r, g, b;

    RGBColorComponent(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b) { }
    RGBColorComponent(const RGBColorComponent& other) : r(other.r), g(other.g), b(other.b) { }
};

struct SoundComponent : public IComponent {
    Sound Sound;
    
    SoundComponent(const std::string& file_path) : Sound(file_path) { }
};

struct TextureComponent : public IComponent {
    Texture2D Texture;

    TextureComponent() = default;
};

struct TransformComponent : public IComponent {
    Vector2D Coordinate;
    float Rotation;
    Vector2D Scale;

    TransformComponent(const Vector2D& coordinate = Vector2D(), float rotation = 0.0f, const Vector2D& scale = Vector2D(1, 1)) 
        : Coordinate(coordinate), Rotation(rotation), Scale(scale) { }
};

}