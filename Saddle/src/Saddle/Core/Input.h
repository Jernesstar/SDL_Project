#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Saddle {

struct MousePosition {
    int x;
    int y;
};

class Input {
public:
    static bool IsKeyPressed(KeyCode key);
    static bool AreKeysPressed(KeyCode key1, KeyCode key2);
    static bool AreKeysPressed(KeyCode key1, KeyCode key2, KeyCode key3);
    static bool AreKeysPressed(KeyCode key1, KeyCode key2, KeyCode key, KeyCode key4);

    static bool IsMouseButtonPressed(MouseCode mouse_button);

    static MousePosition GetMousePosition();
    static int GetMouseX();
    static int GetMouseY();

private:
    Input() = delete;
    ~Input() = delete;
};

}