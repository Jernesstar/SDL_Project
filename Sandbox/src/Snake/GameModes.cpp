#include "GameModes.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Events/EventSystem.h>

OnePlayerClassicSnake::OnePlayerClassicSnake(const std::string name, uint32_t block_size)
    : GameMode(block_size)
{
    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [this](const WindowResizedEvent& event) {
        this->m_ScreenSize = glm::vec2(event.Width, event.Height);
        this->TileBackground();
    });

    InitSprites();
    Player1 = std::make_unique<Snake>(InputMode::Keys, block_size, name);

    m_ScreenSize = Application::Get().GetWindow().GetFrameBufferSize();

    dark_green = new uint8_t[BlockSize * BlockSize * 4];
    light_green = new uint8_t[BlockSize * BlockSize * 4];

    for(uint32_t i = 0; i <= BlockSize * BlockSize * 4; i += 4)
    {
        light_green[i + 0] = 0x00;
        light_green[i + 1] = 0xff;
        light_green[i + 2] = 0x00;
        light_green[i + 3] = 0xff;

        dark_green[i + 0] = 0x00;
        dark_green[i + 1] = 0x82;
        dark_green[i + 2] = 0x00;
        dark_green[i + 3] = 0xff;
    }

    TileBackground();
}

void OnePlayerClassicSnake::Run()
{
    Player1->Reset(glm::vec2{ 525.0f, 425.0f }, glm::vec2{ 1.0f, 0.0f }, 0.05f, 3);
    GameOver = false;
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

void OnePlayerClassicSnake::TileBackground()
{
    delete m_Background;
    m_Background = new Texture2D(m_ScreenSize.x, m_ScreenSize.y);

    std::vector<uint8_t*> colors = { dark_green, light_green };

    for(uint32_t y = 0; y < (uint32_t)floor(m_ScreenSize.y / BlockSize); y++)
    {
        for(uint32_t x = 0; x < (uint32_t)floor(m_ScreenSize.x / BlockSize); x++)
        {
            m_Background->SetData(colors[x % 2], { x * BlockSize, y * BlockSize }, { BlockSize, BlockSize });
        }

        uint8_t* temp = colors[0];
        colors[0] = colors[1];
        colors[1] = temp;
    }
    
}