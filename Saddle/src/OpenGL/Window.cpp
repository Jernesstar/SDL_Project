#include "Window.h"

#include <glad/glad.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Window::Window() : Width(0), Height(0), Title("Window") { }

Window::Window(const WindowSpecification& specs)
    : Width(specs.Width), Height(specs.Height), Title(specs.Title)
{
    // Create a window with width and height, have it not be fullscreen and not share resources
    m_Window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
    SADDLE_CORE_ASSERT(m_Window, "Could not create the window");

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(0); // Note: Maybe include flag in WindowSpecification for this

    SADDLE_CORE_ASSERT(gladLoadGL(), "Glad could not load OpenGL");

    EventSystem::PriorityWindowClosedEventCallbacks.push_back(
        [](WindowClosedEvent& event) {
            Application::Close();
        }
    );
    EventSystem::PriorityWindowResizedEventCallbacks.push_back(
        [this](WindowResizedEvent& event) {
            this->Width = event.Width;
            this->Height = event.Height;
        }
    );
}

Window::~Window()
{
    if(m_Window) glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

GLFWwindow* Window::GetNativeWindow()
{
    return m_Window;
}

}