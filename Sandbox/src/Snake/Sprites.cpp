#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

Snake::Snake(Scene* scene, InputMode mode, uint32_t block_size, const std::string& name)
    : Entity(*scene), Mode(mode), BlockSize(block_size), Name(name), m_Scene(scene) { }

void Snake::Reset(const glm::vec2& head_position, const glm::vec2& direction)
{
    m_Size = 3;
    m_Score = 0;
    m_Blocks.clear();

    for(int i = 0; i < m_Size; i++)
    {
        m_Blocks.push_back(Block(m_Scene, head_position + float(i * BlockSize) * direction));
    }
}

void Snake::Update(TimeStep ts)
{
    glm::vec2 dir = GameInput::GetInput(this->Mode);
    glm::vec2 curr_dir = m_Blocks[m_Size - 1].GetPosition() - m_Blocks[m_Size - 2].GetPosition();
    curr_dir /= abs(curr_dir);

    if(dir.x * curr_dir.x == -1.0f || dir.y * curr_dir.y == -1.0f) // Input asks for opposite direction
        dir == curr_dir;

    Block new_block = Block(m_Scene, glm::vec2(m_Blocks[m_Size - 1].GetPosition()) + (float)BlockSize * dir);
    m_Blocks.push_back(new_block);

    if(m_Blocks.size() > m_Size)
        m_Blocks.erase(m_Blocks.begin());
}

void Snake::Render()
{
    for(Block& block : m_Blocks)
        Renderer2D::DrawEntity(block, glm::vec2(BlockSize));
}