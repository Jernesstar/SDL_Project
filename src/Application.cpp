#include "Application.h"

#include <exception>

namespace Saddle {

Application::Application() { }

Application::~Application()
{
    Mix_CloseAudio();
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
    
    s_Instance = new Application();
    s_Instance->m_Window = new Window(specification.Window_Specification);
    s_Specification = (ApplicationSpecification*)(&specification);
}

void Application::Close()
{
    delete s_Specification;
    delete s_Instance->m_Window;
    delete s_Instance;
}

}