#include "Application.h"

#include <exception>

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : s_Specification(specs), m_Window(specs.Window_Specification)
{
    if(s_Instance)
        throw std::logic_error("Application already exists!");
    s_Instance = this;
}

Application::~Application() { }

void Application::Init(const ApplicationSpecification& specs)
{    
    if(s_Instance)
        throw std::logic_error("Application already exists!");

    auto sound_specs = specs.Sound_Specification;
    
    SDL_Init(specs.SDL_Init_Flags);
    IMG_Init(specs.IMG_Init_Flags);
    TTF_Init();
    Mix_OpenAudio(sound_specs.Frequency, sound_specs.Format, sound_specs.ChannelCount, sound_specs.ChunckSize);
}

void Application::Close()
{
    delete s_Instance;

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::Run()
{

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