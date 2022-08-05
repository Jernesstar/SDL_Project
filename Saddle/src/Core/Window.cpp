#include "Window.h"

namespace Saddle {

Window::Window() : Width(0), Height(0)  { }

Window::Window(const WindowSpecification& specs)
    : Width(specs.Width), Height(specs.Height)
{
    m_Window = SDL_CreateWindow(
        specs.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
}

Window::~Window()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

void Window::HandleEvent(SDL_Event& event)
{
    
}

SDL_Window* Window::GetWindow()
{
    return m_Window;
}

SDL_Renderer* Window::GetRenderer()
{
    return m_Renderer;
}

}