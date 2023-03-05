#pragma once

#include "Saddle/Core/Input.h"

using namespace Saddle;

enum class InputMode { Keys, WASD };

class GameInput {
public:
    static glm::vec2 GetInputKeys()
    {
        if(int x = (int)Input::KeyPressed(Key::Right) - (int)Input::KeyPressed(Key::Left))
            return { (float)x, 0.0f };
        if(int y = (int)Input::KeyPressed(Key::Up) - (int)Input::KeyPressed(Key::Down))
            return { 0.0f, (float)y };
        return { 0.0f, 0.0f };
    }

    static glm::vec2 GetInputWASD()
    {
        if(int x = (int)Input::KeyPressed(Key::A) - (int)Input::KeyPressed(Key::D))
            return { (float)x, 0.0f };
        if(int y = (int)Input::KeyPressed(Key::W) - (int)Input::KeyPressed(Key::S))
            return { 0.0f, (float)y };
        return { 0.0f, 0.0f };
    };

    static glm::vec2 GetInput(InputMode mode) { return mode == InputMode::Keys ? GetInputKeys() : GetInputWASD(); }
};