#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

Snake::Snake(InputMode mode, float block_size, const std::string& name)
    : Entity(), Mode(mode), BlockSize(block_size), Name(name)
{
    Reset({ 0.0f, 0.0f }, { 1.0f, 0.0f });
}

void Snake::Reset(const glm::vec2& head, const glm::vec2& dir, float speed)
{
    Size = 5;
    Score = 0;
    Speed = speed;
    Head = head;
    Direction = dir;
    m_Index = Size - 1;

    m_Blocks.clear();

    for(float i = 0.0f; i < Size; i++)
    {
        Block new_block(head - i * BlockSize * dir, dir);
        m_Blocks.push_back(new_block);
    }
}

void Snake::Increment()
{
    Size++;
    Score++;
}

void Snake::Update(TimeStep ts)
{
    glm::vec2 dir = GameInput::GetInput(Mode);

    if(dir == glm::vec2(0.0f, 0.0f))
        return; // dir = Direction;
    if(dir.x * Direction.x == -1.0f || dir.y * Direction.y == -1.0f)
        return;

    Direction = dir;

    Head += BlockSize * Direction;

    m_Blocks.emplace(m_Blocks.begin(), Head, Direction);

    if(Size < m_Blocks.size())
        m_Blocks.erase(m_Blocks.end());
}

void Snake::Render()
{
    for(Block& block : m_Blocks)
        Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f, 1.0f }, block.GetPosition(), glm::vec2(BlockSize));
}