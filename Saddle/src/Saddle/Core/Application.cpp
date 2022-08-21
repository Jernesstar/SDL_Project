#include "Application.h"

#include "Assert.h"
#include "SDL/Font.h"
#include "Saddle/Events/ApplicationEvents.h"
#include "Saddle/Events/EventDispatcher.h"
#include "Saddle/Renderer/Renderer.h"

namespace Saddle {

Application::Application()
    : m_Window(s_Specification->Window_Specification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    
    s_Instance = this;
    Renderer::Init();

    EventDispatcher::RegisterEventListener<WindowClosedEvent>(
        [](WindowClosedEvent& event) {
            Application::Close();
        }
    );
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");

    s_Specification = (ApplicationSpecification*)(&specs);
    
    SDL_Init(specs.SDL_Init_Flags);
    IMG_Init(specs.IMG_Init_Flags);
    TTF_Init();

    Audio::Init(specs.Audio_Specification);
}

void Application::Close()
{
    delete s_Instance;

    Audio::Shutdown();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

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