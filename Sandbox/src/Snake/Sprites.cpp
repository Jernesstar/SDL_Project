#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

Snake::Snake(InputMode mode, float block_size, const std::string& name)
    : Entity(), Mode(mode), BlockSize(block_size), Name(name)
{
    Reset({ 0.0f, 0.0f }, { 1.0f, 0.0f });
}

void Snake::Reset(const glm::vec2& head_position, const glm::vec2& direction)
{
    m_Size = 3;
    m_Score = 0;
    m_Blocks.clear();

    for(float i = m_Size; i > 0; i--)
    {
        Block new_block(head_position - i * BlockSize * direction);
        m_Blocks.push_back(new_block);
    }

    m_Direction = m_Blocks[m_Size - 1].GetPosition() - m_Blocks[m_Size - 2].GetPosition();
    m_Direction /= abs(m_Direction);
}

void Snake::Update(TimeStep ts)
{
    glm::vec2 dir = GameInput::GetInput(this->Mode);

    if(dir == glm::vec2(0.0f, 0.0f))
        return; // dir = m_Direction;
    if(dir.x * m_Direction.x == -1.0f || dir.y * m_Direction.y == -1.0f) // Input asks for opposite direction
        return;
    m_Direction = dir;

    Block new_block(m_Blocks[m_Size - 1].GetPosition() + BlockSize * dir);
    m_Blocks.push_back(new_block);

    if(m_Blocks.size() > m_Size)
        m_Blocks.erase(m_Blocks.begin());
}

void Snake::Render()
{
    for(Block& block : m_Blocks)
        Renderer2D::DrawQuad(block.GetTexture(), block.GetPosition(), glm::vec2(BlockSize));
}