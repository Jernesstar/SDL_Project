#pragma once

#include <functional>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Saddle/Events/EventSystem.h"
#include "Saddle/Events/KeyEvents.h"
#include "Saddle/Events/MouseEvents.h"
#include "Saddle/Events/WindowEvents.h"
#include "Saddle/Events/EventCallback.h"

#include "OpenGL/Texture2D.h"

namespace Saddle {

struct EventListenerComponent {
    EventCallback<KeyPressedEvent>          OnKeyPressed;
    EventCallback<KeyReleasedEvent>         OnKeyReleased;
    EventCallback<MouseMovedEvent>          OnMouseMoved;
    EventCallback<MouseScrolledEvent>       OnMouseScrolled;
    EventCallback<MouseButtonPressedEvent>  OnMouseButtonPressed;
    EventCallback<MouseButtonReleasedEvent> OnMouseButtonReleased;
    EventCallback<WindowResizedEvent>       OnWindowResized;
    EventCallback<WindowClosedEvent>        OnWindowClosed;

    EventListenerComponent() = default;
    EventListenerComponent(const EventListenerComponent& other) = default;

    void RegisterCallbacks()
    {
        EventSystem::RegisterEventListener(this->OnKeyPressed);
        EventSystem::RegisterEventListener(this->OnKeyReleased);
        EventSystem::RegisterEventListener(this->OnMouseMoved);
        EventSystem::RegisterEventListener(this->OnMouseScrolled);
        EventSystem::RegisterEventListener(this->OnMouseButtonPressed);
        EventSystem::RegisterEventListener(this->OnMouseButtonReleased);
        EventSystem::RegisterEventListener(this->OnWindowResized);
        EventSystem::RegisterEventListener(this->OnWindowClosed);
    }
};

struct TagComponent {
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent& other) = default;
    TagComponent(const std::string& tag) : Tag(tag) { }
};

struct TextureComponent {
    Texture2D* Texture;

    TextureComponent() = default;
    TextureComponent(const std::string& path) { Texture = new Texture2D(path); }
    TextureComponent(uint32_t width, uint32_t height) { Texture = new Texture2D(width, height); }
    TextureComponent(const TextureComponent& other) = default;
};

struct TransformComponent {
    glm::vec3 Translation = { 0, 0, 0 };
    glm::vec3 Rotation = { 0, 0, 0 };
    glm::vec3 Scale = { 1, 1, 1 };

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