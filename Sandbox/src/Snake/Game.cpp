#include "Game.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

Game::Game(uint32_t width, uint32_t height)
    : Application(ApplicationSpecification(ApplicationCommandLineArgs(), WindowSpecification("Snake Game", 1250, 750)))
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
    if(Input::KeyPressed(Key::Return) && m_GameMode->GameOver)
        m_GameMode->Run();

    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    m_Camera.SetProjection(0.0f, vec.x, 0.0f, vec.y);

    Renderer::Clear(glm::vec4(1.0f));
    Renderer2D::BeginScene(m_Camera);
    {
        m_GameMode->CheckGameOver(vec);
        if(m_GameMode->GameOver)
            GameOverScreen();
        else
            m_GameMode->Render(ts);
    }
    Renderer2D::EndScene();
}

void Game::GameOverScreen()
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize() / 2.0f;

    Renderer2D::DrawText(m_GameOverText, vec - m_Font.GetSize(m_GameOverText.GetText()) / 2.0f);
    Renderer2D::DrawText(m_ReturnText, vec - glm::vec2{ m_Font.GetSize(m_ReturnText.GetText()).x / 2.0f, m_Font.GetSize(m_ReturnText.GetText()).y + 25.0f });
}