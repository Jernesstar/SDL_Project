#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

namespace Saddle {

struct WindowSpecification {
    const std::string Title;
    int Width, Height;
    bool VSync;

    WindowSpecification(const std::string& title = "Window", int width = 1200, int height = 640, bool vsync = false)
        : Title(title), Width(width), Height(height), VSync(vsync) { }  
};

class Window {
public:
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    void SetTitle(const std::string& title);
    void SetFramebufferSize(int width, int height);
    void SetVSync(bool vsync);

    bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

    glm::vec2 GetFrameBufferSize();
    GLFWwindow* GetNativeWindow();

private:
    int m_Width, m_Height;
    bool m_VSync;
    std::string m_Title;

    GLFWwindow* m_Window = nullptr;
};

}