#include "Application.h"

#include <exception>

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : s_Specification(specs), m_Window(specs.Window_Specification)
{

}

Application::~Application()
{
    // 
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::Init(const ApplicationSpecification& specification)
{
    SDL_Init(specification.SDL_Init_Flags);
    IMG_Init(specification.IMG_Init_Flags);
    TTF_Init();

    if(s_Instance)
        throw std::logic_error("Application already exists!");
    
    s_Instance = new Application(specification);
}

void Application::Close()
{
    delete s_Instance;
}

Application& Application::Get()
{
    return *s_Instance;
}

Window& Application::GetWindow()
{
    return m_Window;
}

}