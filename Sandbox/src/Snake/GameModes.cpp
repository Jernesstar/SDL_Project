#include "GameModes.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

OnePlayerClassicSnake::OnePlayerClassicSnake(const std::string name, uint32_t block_size)
    : GameMode()
{
    BlockSize = block_size;
    Player1 = new Snake(InputMode::Keys, block_size, name);
    Player2 = nullptr;
}

void OnePlayerClassicSnake::Run()
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    Camera.SetProjection(0.0f, vec.x, 0.0f, vec.y);

    Apple apple;
    apple.SetPosition({ 500.0f, 500.0f });

    Block block;
    block.SetPosition({ 500.0f, 500.0f });

    Player1->Reset(glm::vec2{ 500.0f, 500.0f }, glm::vec2{ 1.0f, 0.0f });
    
    Renderer::Clear(glm::vec4(1.0f));
    Renderer2D::BeginScene(Camera);
    {
        Renderer2D::DrawQuad(block.GetTexture(), block.GetPosition(), glm::vec2(BlockSize));
        Renderer2D::DrawQuad(apple.GetTexture(), apple.GetPosition(), glm::vec2(BlockSize));
        Player1->Render();
    }
    Renderer2D::EndScene();
}