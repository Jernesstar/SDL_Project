#include "Application.h"

#include "Assert.h"

#include <GLFW/glfw3.h>

namespace Saddle {

Application::Application()
    : m_Window(s_Specification->Window_Specification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    
    s_Instance = this;
    // Renderer::Init();
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");
    s_Specification = (ApplicationSpecification*)(&specs);
    SADDLE_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW");
}

void Application::Close()
{
    delete s_Instance;

    glfwTerminate();
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