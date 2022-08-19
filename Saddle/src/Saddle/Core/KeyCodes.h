#pragma once

namespace Saddle {

using KeyCode = unsigned short; // uint16_t

enum Key : KeyCode {
    // From SDL_scancode.h

    // Letter keys
    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    // Symbol keys
    Minus = 45, /* - */
    Equals = 46, /* = */
    LeftBracket = 47, /* [ */
    RightBracket = 48, /* ] */
    Backslash = 49, /* \ */ 
    Semicolon = 51, /* ; */
    Apostrophe = 52, /* ' */
    Backtick = 53, /* ` */
    Comma = 54, /* , */
    Period = 55, /* . */
    ForwardSlash = 56, /* / */

    // Number keys
    N_1 = 30, /* 1 */
    N_2 = 31, /* 2 */
    N_3 = 32, /* 3 */
    N_4 = 33, /* 4 */
    N_5 = 34, /* 5 */
    N_6 = 35, /* 6 */
    N_7 = 36, /* 7 */
    N_8 = 37, /* 8 */
    N_9 = 38, /* 9 */
    N_0 = 39, /* 0 */

    // Function keys
    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,
    F13 = 104,
    F14 = 105,
    F15 = 106,
    F16 = 107,
    F17 = 108,
    F18 = 109,
    F19 = 110,
    F20 = 111,
    F21 = 112,
    F22 = 113,
    F23 = 114,
    F24 = 115,

    Return = 40,
    Escape = 41,
    Backspace = 42,
    Tab = 43,
    Space = 44,
    CapsLock = 57,
    PrintScreen = 70,
    ScrollLock = 71,
    Pause = 72,
    Insert = 73,
    Home = 74,
    PageUp = 75,
    Delete = 76,
    End = 77,
    PageDown = 78,
    NumLock = 83,

    LeftCtrl = 224,
    RightCtrl = 228,
    LeftShift = 225,
    RightShift = 229,
    LeftAlt = 226, 
    RightAlt = 230,
    WindowsKey = 227, /* LGUI in SDL */
    
    Mute = 127,
    VolumeUp = 128,
    VolumeDown = 129,

    // Directional keys
    Right = 79,
    Left = 80,
    Down = 81,
    Up = 82,
    
    // Keypad
    KP_1 = 89,
    KP_2 = 90,
    KP_3 = 91,
    KP_4 = 92,
    KP_5 = 93,
    KP_6 = 94,
    KP_7 = 95,
    KP_8 = 96,
    KP_9 = 97,
    KP_0 = 98,
    KP_Divide = 84,
    KP_Multiply = 85,
    KP_Minus = 86,
    KP_Plus = 87,
    KP_Enter = 88,
    KP_Period = 99,
    KP_Equals = 103,
    KP_Comma = 133,

    // General case between two buttons
    Ctrl = LeftCtrl + RightCtrl,
    Shift = LeftShift + RightShift,
    Alt = LeftAlt + RightAlt,
};

}