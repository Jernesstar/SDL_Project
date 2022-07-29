#include "Window.h"

namespace Saddle {

Window::Window() : Width(0), Height(0)  { }

Window::Window(const WindowSpecification& specs)
    : m_UIElements(), m_GameObjects(), m_Sounds(), Width(specs.Width), Height(specs.Height)
{
    m_Window = SDL_CreateWindow(specs.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
}

Window::~Window()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

void Window::AddUIElement(UI::UIElement& element)
{
    m_UIElements.push_back(&element);
}

void Window::AddGameObject(GameObject& game_object)
{
    m_GameObjects.push_back(&game_object);
}

void Window::AddSound(Sound& sound)
{
    m_Sounds.push_back(&sound);
}

void Window::RenderUI()
{
    SDL_RenderClear(m_Renderer);
    while(m_UIElements.size() > 0)
    {
        UI::UIElement* element = m_UIElements[m_UIElements.size() - 1];
        SDL_RenderCopy(m_Renderer, element->GetTexture(), NULL, &element->GetRect());
        m_UIElements.pop_back();
    }
    SDL_RenderPresent(m_Renderer);
}

void Window::RenderGameObjects()
{
    SDL_RenderClear(m_Renderer);
    while(m_GameObjects.size() > 0)
    {
        GameObject* game_object = m_GameObjects[m_GameObjects.size() - 1];
        SDL_RenderCopy(m_Renderer, game_object->GetTexture(), NULL, &game_object->GetRect());
        m_GameObjects.pop_back();
    }
    SDL_RenderPresent(m_Renderer);
}

void Window::RenderScene()
{
    RenderGameObjects();
    RenderUI();
}

void Window::HandleEvent(SDL_Event& event)
{
    for(int i = 0; i < m_UIElements.size(); i++)
    {
        m_UIElements[i]->OnEvent(event);
    }
    for(int i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->OnEvent(event);
    }
}

SDL_Renderer* Window::GetRenderer()
{
    return m_Renderer;
}

SDL_Window* Window::GetWindow()
{
    return m_Window;
}

}