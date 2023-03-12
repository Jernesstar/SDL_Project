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
    Player1->Reset(glm::vec2{ 500.0f, 500.0f }, glm::vec2{ 1.0f, 0.0f }, 0.05f, 20);
}

void OnePlayerClassicSnake::Render(TimeStep ts)
{
    Player1->Update(ts);
    Player1->Render();
}

void OnePlayerClassicSnake::CheckGameOver(glm::vec2 bound)
{
    for(uint32_t i = 1; i < Player1->Size; i++)
    {
        if(Player1->Blocks[i].GetPosition() == Player1->Head)
        {
            GameOver = true;
            return;
        }
    }

    if(Player1->Head.x < 0.0f || Player1->Head.x > bound.x || Player1->Head.y < 0.0f || Player1->Head.y > bound.y)
        GameOver = true;
}