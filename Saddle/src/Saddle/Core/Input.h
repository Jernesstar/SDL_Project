#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include "SDL/Rect.h"
#include "SDL/Transform.h"
#include "Saddle/Math/Vector.h"

namespace Saddle {

class Input {
public:
    static bool KeyPressed(KeyCode key);
    static bool KeysPressed(KeyCode key1, KeyCode key2);
    static bool KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3);
    static bool KeysPressed(KeyCode key1, KeyCode key2, KeyCode key, KeyCode key4);

    static bool MouseButtonPressed(MouseCode mouse_button);
    static bool MousePressedOn(const Rect& rect, const Transform& transform);

    static Vector2D GetMousePosition();
    static int GetMouseX();
    static int GetMouseY();

private:
    Input() = delete;
    ~Input() = delete;
};

}