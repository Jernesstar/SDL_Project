#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#include "Assert.h"
#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Application::Application()
    : m_Window(s_Specification->Window_Specification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    
    s_Instance = this;
    glfwMakeContextCurrent(m_Window.GetNativeWindow());
    SADDLE_CORE_ASSERT(gladLoadGL(), "Glad could not load OpenGL");

    // Renderer::Init();
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");
    s_Specification = (ApplicationSpecification*)(&specs);
    SADDLE_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW");

    // EventSystem::Init();
    // Audio::Init();
    // Image::Init();
}

void Application::Close()
{
    delete s_Instance;

    glfwTerminate();
    exit(0);
}

void Application::Run() { }

Application& Application::Get()
{
    return *s_Instance;
}

Window& Application::GetWindow()
{
    return m_Window;
}

}