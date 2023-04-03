#pragma once

#include <memory>

#include "Saddle/Renderer/Camera.h" 
#include "Saddle/Events/Events.h"
#include "Saddle/Core/Time.h"
#include "Saddle/Core/Codes.h"

namespace Saddle {

class CameraController {
public:
    struct MovementOptions {
    private:
        enum class Options { Up, Down, Left, Right, Forward, Backward };

        KeyCode Get(std::unordered_map<Options, KeyCode> options, Options option, KeyCode default_val)
        {
            if(options.find(option) != options.end())
                return options[option];
            return default_val;
        }

    public:
        const KeyCode UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD;

        MovementOptions(
            KeyCode up   = Key::Q,
            KeyCode down  = Key::E,
            KeyCode left  = Key::A,
            KeyCode right = Key::D,
            KeyCode forward  = Key::W,
            KeyCode backward = Key::S
        ) : UP(up), DOWN(down), LEFT(left), RIGHT(right), FORWARD(forward), BACKWARD(backward) { }

        MovementOptions(std::unordered_map<Options, KeyCode> map)
            : UP(Get(map, Options::Up, Key::Q)),
              DOWN(Get(map, Options::Down, Key::E)),
              LEFT(Get(map, Options::Left, Key::A)),
              RIGHT(Get(map, Options::Right, Key::D)),
              FORWARD(Get(map, Options::Forward, Key::W)),
              BACKWARD(Get(map, Options::Backward, Key::S)) { }
    };

public:
    float TranslationSpeed = 0.005f;
    float RotationSpeed = 0.3f;

public:
    CameraController(Camera& camera, MovementOptions options = { });

    void OnUpdate(TimeStep ts);
    void OnMouseEvent(const MouseEvent& event);
    void OnResize();

private:
    glm::vec2 m_LastMousePosition = { 0.0f, 0.0f };

    Camera* m_Camera;
};

}


