#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

Snake::Snake(InputMode mode, uint32_t block_size, const std::string& name)
    : Entity(), Mode(mode), BlockSize(block_size), Name(name)
{
    Reset({ 0.0f, 0.0f }, { 1.0f, 0.0f });
}

void Snake::Reset(const glm::vec2& head, const glm::vec2& dir, float speed, uint32_t size)
{
    Size = size;
    Score = 0;
    Speed = speed;
    Head = head;
    Direction = dir;

    Blocks.clear();

    for(float i = 0.0f; i < Size; i++)
    {
        Block new_block(head - i * BlockSize * dir, dir);
        Blocks.push_back(new_block);
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
    Head = Blocks[1].GetPosition() + (float)BlockSize * Direction;
    Blocks[0].SetPosition(Head);
    Blocks[0].Velocity = Direction;

    for(uint32_t i = Size - 1; i > 0; i--)
    {
        Block& curr = Blocks[i];
        Block& next = Blocks[i - 1];

        if(curr.Velocity == next.Velocity)
            curr.SetPosition(curr.GetPosition() + Speed * BlockSize * curr.Velocity);
        else
        {
            curr.Velocity = next.Velocity;
            curr.SetPosition(curr.GetPosition() + Speed * BlockSize * curr.Velocity);
        }
    }
}

void Snake::Render()
{
    for(Block& block : Blocks)
        Renderer2D::DrawQuad(block.GetImage(), block.GetPosition(), glm::vec2(BlockSize));
}