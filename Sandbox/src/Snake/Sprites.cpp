#include "Sprites.h"

#include <memory>

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

struct Directions {
    glm::vec2 First, Second;

    bool operator ==(const Directions& other) const { return First == other.First && Second == other.Second; }
};

namespace std {

template<>
struct hash<Directions> {
    std::size_t operator ()(const Directions& dir) const
    {
        glm::ivec2 f = glm::ivec2(dir.First);
        glm::ivec2 s = glm::ivec2(dir.Second);

        return (f.x << 2) ^ (s.x << 4) ^ (f.y << 6) ^ (s.y << 8);
    }
};

}

struct TextureAndTransform {
    glm::vec3 Rotation;
    uint32_t TextureIndex;
};

static std::unordered_map<uint32_t, std::unique_ptr<Texture2D>> Images;
static std::unordered_map<Directions, TextureAndTransform> Transforms
{
    { { { }, { } }, { { 0.0f, 0.0f, 0.0f }, 0 } }
};

static inline const glm::vec2 LEFT  = { -1.0f,  0.0f };
static inline const glm::vec2 RIGHT = {  1.0f,  0.0f };
static inline const glm::vec2 UP    = {  0.0f,  1.0f };
static inline const glm::vec2 DOWN  = {  0.0f, -1.0f };

void InitSprites()
{
    Images[0] = std::make_unique<Texture2D>("Sandbox/assets/images/block_straight.png");
    Images[1] = std::make_unique<Texture2D>("Sandbox/assets/images/block_left_up.png");
    Images[2] = std::make_unique<Texture2D>("Sandbox/assets/images/block_right_up.png");
    Images[3] = std::make_unique<Texture2D>("Sandbox/assets/images/apple.png");
}

Apple::Apple(const glm::vec2& position)
{
    this->AddComponent<TextureComponent>().Texture = Images[3].get();
    this->AddComponent<TransformComponent>().Translation = glm::vec3(position, 0.0f);
}

void Block::SetImage(glm::vec2 first, glm::vec2 second)
{
    auto& tat = Transforms[{ first, second }];
    this->GetComponent<TextureComponent>().Texture = Images[tat.TextureIndex].get();
    this->GetComponent<TransformComponent>().Rotation = tat.Rotation;
}

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