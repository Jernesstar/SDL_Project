#include "Window.h"

#include <glad/glad.h>

#include <stb_image/stb_image.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Utils.h"
#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Window::Window(const WindowSpecification& specs)
    : m_Specs(specs)
{
    // Create a window with width and height, have it not be fullscreen and not share resources
    m_Window = glfwCreateWindow(specs.Width, specs.Height, specs.Title.c_str(), nullptr, nullptr);
    SADDLE_CORE_ASSERT(m_Window, "Could not create the window");

    glfwMakeContextCurrent(m_Window);

    SetVSync(specs.VSync);
    SetWindowIcon(specs.IconPath);

    EventSystem::RegisterEventListener<WindowClosedEvent>(
    [](const WindowClosedEvent& event) {
        Application::Close();
    });

    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [this](const WindowResizedEvent& event) {
        SetFramebufferSize(event.Width, event.Height);
    });
}

Window::~Window()
{
    if(m_Window) glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Window::SetWindowIcon(const std::string& path)
{
    if(path == "") 
    {
        glfwSetWindowIcon(m_Window, 0, nullptr);
        return;
    }

    GLFWimage icon;
    icon.pixels = Utils::LoadImage(path, 4, false);
    glfwSetWindowIcon(m_Window, 1, &icon);
    stbi_image_free(icon.pixels);
}

void Window::SetTitle(const std::string& title) { glfwSetWindowTitle(m_Window, title.c_str()); }
void Window::SetVSync(bool vsync) { glfwSwapInterval((int)vsync); }

void Window::SetFramebufferSize(uint32_t width, uint32_t height)
{
    m_Specs.Width = width;
    m_Specs.Height = height;
    glViewport(0, 0, width, height);
}

const std::string& Window::GetTitle() const { return m_Specs.Title; }

glm::vec2 Window::GetFrameBufferSize() const
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return { width, height };
}

GLFWwindow* Window::GetNativeWindow() const
{
    return m_Window;
}

}