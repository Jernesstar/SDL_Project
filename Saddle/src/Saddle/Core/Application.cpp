#include "Application.h"

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : s_Specification(specs), m_Window(specs.Window_Specification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    
    s_Instance = this;
    Renderer::Init();
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");

    SDL_Init(specs.SDL_Init_Flags);
    IMG_Init(specs.IMG_Init_Flags);
    TTF_Init();

    Audio::Init(specs.Audio_Specification);
}

void Application::Close()
{
    delete s_Instance;

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
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