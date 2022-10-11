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

    WindowSpecification(const std::string& title = "Window", int width = 1200, int height = 640, bool vsync = true)
        : Title(title), Width(width), Height(height), VSync(vsync) { }  
};

class Window {
public:
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    void SetTitle(const std::string& title);
    void SetVSync(bool vsync);
    void SetFramebufferSize(uint32_t width, uint32_t height);

    bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

    const std::string& GetTitle() const;
    glm::vec2 GetFrameBufferSize() const;
    GLFWwindow* GetNativeWindow() const;

private:
    uint32_t m_Width, m_Height;
    bool m_VSync;
    std::string m_Title;

    GLFWwindow* m_Window = nullptr;
};

}