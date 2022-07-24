#include "Application.h"

#include <exception>

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : m_Specification(specs)
{
    if(!instance)
        instance = this;
    else
        throw std::logic_error("Application already exists!");

    window = new Window(specs.Window_Specs);
}

Application::~Application()
{
    Mix_CloseAudio();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::Init(Uint32 sdl_init_flags, Uint32 img_init_flags)
{
    SDL_Init(sdl_init_flags);
    IMG_Init(img_init_flags);
    TTF_Init();
}

}