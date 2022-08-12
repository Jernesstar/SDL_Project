#pragma once

#include <vector>

#include "KeyCodes.h"
#include "MouseCodes.h"


namespace Saddle {

struct MousePosition {
    int x;
    int y;
};

class Input {

public:
    static bool IsKeyPressed(Key key);
    
    static bool IsMouseButtonPressed(Mouse mouse_button);
    static MousePosition GetMousePosition();
    static int GetMouseX();
    static int GetMouseY();

private:
    Input() = delete;
    ~Input() = delete;

};

}