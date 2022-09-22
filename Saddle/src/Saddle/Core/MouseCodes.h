#pragma once

namespace Saddle {

using MouseCode = unsigned char; // uint8_t

enum Mouse : MouseCode {
    // From glfw3.h starting line 571

    Button1 = 0,
    Button2 = 1,
    Button3 = 2,
    Button4 = 3,
    Button5 = 4,
    Button6 = 5,
    Button7 = 6,
    Button8 = 7,

    LeftButton   = Button1,
    MiddleButton = Button2,
    RightButton  = Button3
};

}