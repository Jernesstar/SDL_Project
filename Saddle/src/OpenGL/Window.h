#pragma once

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Saddle {

struct WindowSpecification {
    const std::string Title;
    int Width, Height;

    WindowSpecification(const std::string& title = "Window", int width = 1200, int height = 640)
        : Title(title), Width(width), Height(height) { }  
};

class Window {
public:
    int Width, Height;
    std::string Title;

public:
    Window();
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    GLFWwindow* GetNativeWindow();

private:
    GLFWwindow* m_Window = nullptr;
};

}