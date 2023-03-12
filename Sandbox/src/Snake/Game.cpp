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
    m_GameMode->Run();
}

void Game::OnUpdate(TimeStep ts)
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    m_Camera.SetProjection(0.0f, vec.x, 0.0f, vec.y);

    Renderer::Clear(glm::vec4(1.0f));
    Renderer2D::BeginScene(m_Camera);
    {
        m_GameMode->CheckGameOver(vec);
        if(m_GameMode->GameOver)
            ShowGameOver();
        else
            m_GameMode->Render(ts);
    }
    Renderer2D::EndScene();
}

void Game::ShowGameOver()
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize() / 2.0f;
    vec.x -= m_Font.GetSize(m_GameOverText.GetText()).x / 2.0f;

    Renderer2D::DrawText(m_GameOverText, vec);
}