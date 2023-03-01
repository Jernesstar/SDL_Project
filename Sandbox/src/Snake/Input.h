#pragma once

#include "Saddle/Core/Input.h"

using namespace Saddle;

enum class InputMode { Keys, WASD };

class GameInput {
public:
    static glm::vec2 GetInputKeys();
    static glm::vec2 GetInputWASD();
    static glm::vec2 GetInput(InputMode mode) { return mode == InputMode::Keys ? GetInputKeys() : GetInputWASD(); }
};

glm::vec2 GameInput::GetInputKeys()
{
    float x = 0.0f, y = 0.0f;

    x = Input::KeyPressed(Key::Left) ? -1.0f : Input::KeyPressed(Key::Right) ? 1.0f : 0.0f;
    y = Input::KeyPressed(Key::Down) ? -1.0f : Input::KeyPressed(Key::Up) ? 1.0f : 0.0f;

    return { x, y };
}

glm::vec2 GameInput::GetInputWASD()
{
    float x = 0.0f, y = 0.0f;

    x = Input::KeyPressed(Key::A) ? -1.0f : Input::KeyPressed(Key::D) ? 1.0f : 0.0f;
    y = Input::KeyPressed(Key::S) ? -1.0f : Input::KeyPressed(Key::W) ? 1.0f : 0.0f;

    return { x, y };
}