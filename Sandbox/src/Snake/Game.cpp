#include "Game.h"

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
    m_GameMode->Run();
}

void Game::OnUpdate(TimeStep ts)
{
    m_GameMode->Update(ts);
    m_GameMode->CheckGameOver();

    if(m_GameMode->GameOver)
        Application::Close();
}