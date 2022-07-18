#include "Window.h"

namespace Saddle {

Window::Window(int width, int height, const std::string& window_title, Uint32 sdl_init_flags)
{
    SDL_Init(sdl_init_flags);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    Mix_CloseAudio();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer** Window::GetRenderer()
{
    return &renderer;
}

SDL_Window** Window::GetWindow()
{
    return &window;
}

}