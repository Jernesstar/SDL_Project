#include "Game.h"

#include <Saddle/Events/EventSystem.h>
#include <Saddle/Core/Input.h>

#include <Saddle/Renderer/Renderer2D.h>

Game::Game()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event) {
        if(event.Key == Key::Escape)
            Application::Close();
    });
}

void Game::OnUpdate(TimeStep ts)
{
    Renderer::Clear({ 1.0f, 0.0f, 0.0f, 1.0f });

    
}
