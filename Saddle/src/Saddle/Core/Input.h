#pragma once

#include <glm/vec2.hpp>

#include "Codes.h"

namespace Saddle {

class Input {
public:
    static bool KeyPressed(KeyCode key);
    static bool KeysPressed(KeyCode key1, KeyCode key2);
    static bool KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3);
    static bool KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3, KeyCode key4);

    static void SetCursorMode(CursorMode mode);
    static bool MouseButtonPressed(MouseCode mouse_button);

    static glm::vec2 GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();

private:
    Input() = delete;
    ~Input() = delete;
};

}