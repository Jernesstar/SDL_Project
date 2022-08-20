#pragma once

namespace Saddle {

struct Rect {
    int Width, Height;

    Rect(int width, int height) : Width(width), Height(height) { }
    Rect(const Rect& other) : Width(other.Width), Height(other.Height) { }
};

}