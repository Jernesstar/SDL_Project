#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#include "Assert.h"
#include "Saddle/Events/EventSystem.h"
#include "Saddle/Events/ApplicationEvents.h"
#include "Saddle/Renderer/Renderer.h"
#include "Saddle/Core/Time.h"

namespace Saddle {

Application::Application()
    : Window(s_Specification.Window_Specification), m_LastFrame(0)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    SADDLE_CORE_ASSERT(gladLoadGL(), "Glad could not load OpenGL");

    s_Instance = this;

    Renderer::Init();
    EventSystem::Init();
}

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");
    SADDLE_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW");

    s_Specification = specs;

    // Audio::Init();
    // Image::Init();
}

void Application::Init(const ApplicationCommandLineArgs& args, const ApplicationSpecification& specs)
{
    Application::Init();
    s_Specification.CommandLineArgs = args;
}

void Application::Run()
{
    while(Window.IsOpen())
    {
        TimePoint time = Time::GetTime();
        TimeStep ts = time - (m_LastFrame != 0 ? m_LastFrame : Time::GetTime());
        m_LastFrame = time;

        Window.Update();

        ApplicationUpdatedEvent event(ts);
        EventSystem::Dispatch(event);
        EventSystem::PollEvents();
    }
}

void Application::Close()
{
    if(s_Instance) delete s_Instance;

    glfwTerminate();
    exit(0);
}

Application& Application::Get()
{
    return *s_Instance;
}

Window& Application::GetWindow()
{
    return Window;
}

}