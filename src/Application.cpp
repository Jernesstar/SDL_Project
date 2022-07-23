#include "Application.h"

#include <exception>

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : m_Specification(specs)
{
    if(!s_Instance)
        s_Instance = this;
    else
        throw std::logic_error("Application already exists!");

    m_Window = new Window(specs.Window_Specs);
}

Application::~Application()
{
    Mix_CloseAudio();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::Init(int sdl_init_flags = SDL_INIT_EVERYTHING, int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP)
{
    SDL_Init(sdl_init_flags);
    IMG_Init(img_init_flags);
    TTF_Init();
}

}