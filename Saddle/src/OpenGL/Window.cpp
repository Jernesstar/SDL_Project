#include "Window.h"

#include <glad/glad.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Window::Window(const WindowSpecification& specs)
    : m_Width(specs.Width), m_Height(specs.Height), m_Title(specs.Title), m_VSync(specs.VSync)
{
    // Create a window with width and height, have it not be fullscreen and not share resources
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    SADDLE_CORE_ASSERT(m_Window, "Could not create the window");

    glfwMakeContextCurrent(m_Window);

    SetVSync(specs.VSync);

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

void Window::SetTitle(const std::string& title) { glfwSetWindowTitle(m_Window, title.c_str()); }
void Window::SetVSync(bool vsync) { glfwSwapInterval(vsync ? 1 : 0); }

void Window::SetFramebufferSize(uint32_t width, uint32_t height)
{
    m_Width = width;
    m_Height = height;
    glViewport(0, 0, width, height);
}

const std::string& Window::GetTitle() const { return m_Title; }

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