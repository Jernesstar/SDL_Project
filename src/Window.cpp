#include "Window.h"

#include <algorithm>
#include <exception>

namespace Saddle {

Window::Window(int width, int height, const std::string& window_title, Uint32 sdl_init_flags) :
ui_elements(), game_objects(), sounds()
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

template<typename T>
void Window::AddElement(const T& element)
{
    if(T == Sound)
        sounds.push_back(element);
    else if(T == UI::UIElement)
        ui_elements.push_back(element);
    else if(T == GameObject)
        game_objects.push_back(element);
    else
        throw std::invalid_argument("Type parameter 'T' must be GameObject, UIElement, or Sound");
}

template<typename T>
void Window::RemoveElement(const T& element)
{
    if(T == Sound)
        auto element = std::remove(sounds.begin(), sounds.end(), _ui_element);
        sounds.erase(element, element);
    if(T == UI::UIElement)
        auto element = std::remove(ui_elements.begin(), ui_elements.end(), _ui_element);
        ui_elements.erase(element, element);
    if(T == GameObject)
        auto element = std::remove(game_objects.begin(), game_objects.end(), _ui_element);
        game_objects.erase(element, element);
    else
        throw std::invalid_argument("Type parameter 'T' must be GameObject, UIElement, or Sound");
}

void Window::RenderUI()
{
    for(UI::UIElement& ui_element : ui_elements)
    {
        SDL_RenderCopy(renderer, *ui_element.GetTexture(), NULL, ui_element.GetRect());
    }
    SDL_RenderPresent(renderer);
}

void Window::RenderGameObjects()
{
    for(GameObject& game_object : game_objects)
    {
        SDL_RenderCopy(renderer, *game_object.GetTexture(), NULL, game_object.GetRect());
    }
    SDL_RenderPresent(renderer);
}

void Window::RenderScene()
{
    RenderUI();
    RenderGameObjects();
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