#pragma once

#include <memory>

#include "Saddle/Renderer/Camera.h" 
#include "Saddle/Events/Events.h"
#include "Saddle/Core/Time.h"
#include "Saddle/Core/Codes.h"

namespace Saddle {

class CameraController {
public:
    struct MovementSettings {
    private:
        enum class Settings { Up, Down, Left, Right, Forward, Backward };

        KeyCode Get(std::unordered_map<Settings, KeyCode> settings, Settings setting, KeyCode default_val)
        {
            return settings.find(setting) != settings.end() ? settings[setting] :  default_val;
        }

    public:
        const KeyCode UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD;

        MovementSettings(
            KeyCode up   = Key::Q,
            KeyCode down  = Key::E,
            KeyCode left  = Key::A,
            KeyCode right = Key::D,
            KeyCode forward  = Key::W,
            KeyCode backward = Key::S
        ) : UP(up), DOWN(down), LEFT(left), RIGHT(right), FORWARD(forward), BACKWARD(backward) { }

        MovementSettings(std::unordered_map<Settings, KeyCode> map)
            : UP(Get(map, Settings::Up, Key::Q)),
              DOWN(Get(map, Settings::Down, Key::E)),
              LEFT(Get(map, Settings::Left, Key::A)),
              RIGHT(Get(map, Settings::Right, Key::D)),
              FORWARD(Get(map, Settings::Forward, Key::W)),
              BACKWARD(Get(map, Settings::Backward, Key::S)) { }
    };

public:
    float TranslationSpeed = 0.005f;
    float RotationSpeed = 0.3f;

public:
    CameraController(Camera& camera, MovementSettings settings = { });

    void OnUpdate(TimeStep ts);
    void OnMouseEvent(const MouseEvent& event);
    void OnResize();

private:
    glm::vec2 m_LastMousePosition = { 0.0f, 0.0f };

    Camera* m_Camera;
    MovementSettings m_MovementSettings;
};

}
