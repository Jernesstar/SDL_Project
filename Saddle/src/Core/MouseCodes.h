#pragma once

namespace Saddle {

using MouseCode = unsigned char; // uint8_t

enum Mouse : MouseCode {
    // From SDL_mouse.h

    LeftButton = 1,
    MiddleButton = 2,
    RightButton = 3
};

}