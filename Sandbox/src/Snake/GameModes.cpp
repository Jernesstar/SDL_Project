#include "GameModes.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

OnePlayerClassicSnake::OnePlayerClassicSnake(const std::string name, uint32_t block_size)
{
    BlockSize = block_size;
    Player1 = std::make_unique<Snake>(InputMode::Keys, block_size, name);

    m_Background = new Texture2D(1900, 600);
    uint32_t* dark_green = new uint32_t[BlockSize * BlockSize * 4];
    uint8_t* light_green = new uint8_t[BlockSize * BlockSize * 4];

    for(uint32_t i = 0; i < BlockSize * BlockSize * 4; i += 4)
    {
        dark_green[i + 0] = 0x00;
        dark_green[i + 1] = 0xff;
        dark_green[i + 2] = 0x00;
        dark_green[i + 3] = 0xff;
    }

    m_Background->SetData(dark_green, { 100, 500 }, { BlockSize, BlockSize });
}

void OnePlayerClassicSnake::Run()
{
    Player1->Reset(glm::vec2{ 500.0f, 500.0f }, glm::vec2{ 1.0f, 0.0f }, 0.05f, 20);
}

void OnePlayerClassicSnake::Render(TimeStep ts)
{
    glm::vec2 vec = Application::Get().GetWindow().GetFrameBufferSize();
    Renderer2D::DrawQuad(m_Background, vec / 2.0f, vec);
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