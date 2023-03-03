#include "Game.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

Game::Game()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event) {
        if(event.Key == Key::Escape)
            Application::Close();
    });

    uint32_t block_size = 50;
    std::string name = "Star";

    m_GameMode = new OnePlayerClassicSnake(name, block_size);
}

void Game::OnUpdate(TimeStep ts)
{
    m_GameMode->Run();
}
