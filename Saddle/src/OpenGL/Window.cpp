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

    SetFramebufferSize(m_Width, m_Height);
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

void Window::SetFramebufferSize(int width, int height)
{
    m_Width = width;
    m_Height = height;
    glViewport(0, 0, width, height);
}

glm::vec2 Window::GetFrameBufferSize()
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return { width, height };
}

GLFWwindow* Window::GetNativeWindow()
{
    return m_Window;
}

}