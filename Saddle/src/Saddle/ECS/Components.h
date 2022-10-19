#pragma once

#include <functional>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Saddle/Events/KeyEvents.h"
#include "Saddle/Events/MouseEvents.h"
#include "Saddle/Events/WindowEvents.h"

#include "OpenGL/Texture2D.h"

namespace Saddle {

struct EventListenerComponent {
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

struct RigidBodyComponent {
    glm::vec2 Velocity;
    float Speed, RotationSpeed, Bounciness;

    RigidBodyComponent(const glm::vec2& velocity = glm::vec2(), float rotation_speed = 0.0f, float bounciness = 0.0f) 
        : RotationSpeed(rotation_speed), Bounciness(bounciness) { }
    
    void Update()
    {
        Speed = glm::length(Velocity);
    }
};

struct RGBColorComponent {
    glm::vec3 Color;

    RGBColorComponent(const glm::vec3& color = { 0, 0, 0 }) : Color(color) { }
    RGBColorComponent(const RGBColorComponent& other) : Color(other.Color) { }
};

// struct SoundComponent {
//     Sound Sound;
//
//     SoundComponent(const std::string& file_path) : Sound(file_path) { }
// };

struct TextureComponent {
    Texture2D Texture;

    TextureComponent(const std::string& path = "") : Texture(path) { }
};

struct TransformComponent {
    glm::vec3 Translation = { 0, 0, 0 };
    glm::vec3 Rotation = { 0, 0, 0 };
    glm::vec3 Scale { 1, 1, 1 };

    TransformComponent() = default;
    TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
        : Translation(translation), Rotation(rotation), Scale(scale) { }

    glm::mat4 GetTransfrom()
    {
        return glm::translate(glm::mat4(1.0f), Translation)
             * glm::toMat4(glm::quat(Rotation))
             * glm::scale(glm::mat4(1.0f), Scale);
    }
};

}