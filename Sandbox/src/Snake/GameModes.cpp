#include "GameModes.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

OnePlayerClassicSnake::OnePlayerClassicSnake(const std::string name, float block_size)
    : GameMode()
{
    BlockSize = block_size;
    Player1 = std::make_unique<Snake>(InputMode::Keys, block_size, name);
}

void OnePlayerClassicSnake::Run()
{
    Player1->Reset(glm::vec2{ 500.0f, 500.0f }, glm::vec2{ 1.0f, 0.0f }, 0.05f);
}

void OnePlayerClassicSnake::Update(TimeStep ts)
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    Camera.SetProjection(0.0f, vec.x, 0.0f, vec.y);

    Player1->Update(ts);

    Renderer::Clear(glm::vec4(1.0f));
    Renderer2D::BeginScene(Camera);
    {
        Player1->Render();
    }
    Renderer2D::EndScene();
}