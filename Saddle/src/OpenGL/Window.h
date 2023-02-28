#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

namespace Saddle {

struct WindowSpecification {
    std::string Title;
    std::string IconPath;
    int Width, Height;
    bool VSync;

    WindowSpecification(const std::string& title = "Window", int width = 1600,
        int height = 900, bool vsync = true, const std::string& icon_path = "")
        : Title(title), Width(width), Height(height), VSync(vsync), IconPath(icon_path) { }
};

class Window {
public:
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    void Update() { glfwSwapBuffers(m_Window); }

    void SetWindowIcon(const std::string& path);
    void SetTitle(const std::string& title);
    void SetVSync(bool vsync);
    void SetFramebufferSize(uint32_t width, uint32_t height);

    bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

    const std::string& GetTitle() const { return m_Specs.Title; }
    glm::vec2 GetFrameBufferSize() const;
    float GetAspectRatio() const { auto v =  GetFrameBufferSize(); return v.x / v.y; }

    GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
    WindowSpecification m_Specs;

    GLFWwindow* m_Window = nullptr;
};

}