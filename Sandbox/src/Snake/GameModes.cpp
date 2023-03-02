#include "GameModes.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

OnePlayerClassicSnake::OnePlayerClassicSnake(const std::string name, uint32_t block_size)
    : GameMode()
{
    BlockSize = block_size;
    Player1 = new Snake(GameMode::Scene, InputMode::Keys, block_size, name);
    Player2 = nullptr;
}

void OnePlayerClassicSnake::Run()
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    Camera.SetProjection(0.0f, vec.x, 0.0f, vec.y);

    Apple apple(GameMode::Scene);
    apple.Position = glm::vec2(500.0f, 500.0f);

    Block block(GameMode::Scene, glm::vec2(500.0f, 500.0f));

    Renderer::Clear(glm::vec4(1.0f));

    Renderer2D::BeginScene(Camera);
    {
        Renderer2D::DrawEntity(block);
        Renderer2D::DrawQuad(apple.GetComponent<TextureComponent>().Texture, apple.Position, glm::vec2(BlockSize));
        Player1->Render();
    }
    Renderer2D::EndScene();
}