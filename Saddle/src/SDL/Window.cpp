#include "Window.h"

#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Window::Window() : Width(0), Height(0)  { }

Window::Window(const WindowSpecification& specs)
    : Width(specs.Width), Height(specs.Height)
{
    m_Window = SDL_CreateWindow(
        specs.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, specs.WindowFlags);
    
    m_Renderer = SDL_CreateRenderer(m_Window, -1, specs.RendererFlags);

    EventSystem::RegisterEventListener<WindowResizedEvent>(
        [this](WindowResizedEvent& event) {
            this->Width = event.Width;
            this->Height = event.Height;
        }
    );
}

Window::~Window()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

SDL_Window* Window::GetNativeWindow()
{
    return m_Window;
}

SDL_Renderer* Window::GetRenderer()
{
    return m_Renderer;
}

}