#include "Application.h"

#include "Assert.h"
#include "SDL/Image.h"
#include "SDL/Font.h"
#include "Saddle/Events/WindowEvents.h"
#include "Saddle/Events/EventSystem.h"
#include "Saddle/Renderer/Renderer.h"

namespace Saddle {

Application::Application()
    : m_Window(s_Specification->Window_Specification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    
    s_Instance = this;
    Renderer::Init();
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");

    s_Specification = (ApplicationSpecification*)(&specs);
    
    SDL_Init(specs.SDL_Init_Flags);
    TTF_Init();

    Image::Init(specs.IMG_Init_Flags);
    Audio::Init(specs.Audio_Specification);
}

void Application::Close()
{
    delete s_Instance;

    Audio::Shutdown();
    Image::Shutdown();
    
    TTF_Quit();
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