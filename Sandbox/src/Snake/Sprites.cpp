#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

struct Directions {
    glm::vec2 First;
    glm::vec2 Second;

    bool operator ==(const Directions& other) const
    {
        return this->First == other.First && this->Second == other.Second;
    }
};

namespace std {

template<>
struct hash<Directions> {
    std::size_t operator ()(const Directions& dir) const
    {
        glm::ivec2 vec1 = glm::ivec2(dir.First + 1.0f);
        glm::ivec2 vec2 = glm::ivec2(dir.Second + 1.0f);

        return (vec1.x << 1) ^ (vec2.x << 2) ^ (vec1.y << 3) ^ (vec2.y << 4);
    }
};

}

struct TextureAndTransform {
    glm::vec3 Rotation;
    uint32_t TextureIndex;
};

static const glm::vec2 LEFT  = { -1.0f,  0.0f };
static const glm::vec2 RIGHT = {  1.0f,  0.0f };
static const glm::vec2 UP    = {  0.0f,  1.0f };
static const glm::vec2 DOWN  = {  0.0f, -1.0f };

static inline std::unordered_map<uint32_t, Texture2D*> Images =
{
    { 0, nullptr },
    { 1, nullptr },
    { 2, nullptr },
};

static inline std::unordered_map<Directions, TextureAndTransform> Transforms =
{
    { { { }, { } },    { {  0.0f, 0.0f, 0.0f }, 0 } },

    { { UP, LEFT },    { {  0.0f, 0.0f, 0.0f }, 1 } },
    { { UP, RIGHT },   { {  0.0f, 0.0f, 0.0f }, 2 } },
    { { DOWN, LEFT },  { { -2.0f, 0.0f, 0.0f }, 1 } },
    { { DOWN, RIGHT }, { { -2.0f, 0.0f, 0.0f }, 2 } },

    { { LEFT, UP },    { {  2.0f, 0.0f, 0.0f }, 2 } },
    { { LEFT, DOWN },  { {  0.0f, 0.0f, 0.0f }, 2 } },
    { { RIGHT, UP },   { {  0.0f, 0.0f, 1.0f }, 2 } },
    { { RIGHT, DOWN }, { { -2.0f, 0.0f, 1.0f }, 2 } },
};


void Block::SetImage(glm::vec2 first, glm::vec2 second)
{
    first = glm::normalize(first);
    second = glm::normalize(second);

    if(Images[0] == nullptr)
    {
        Images[0] = new Texture2D("Sandbox/assets/images/block_straight.png");
        Images[1] = new Texture2D("Sandbox/assets/images/block_left_up.png");
        Images[2] = new Texture2D("Sandbox/assets/images/block_right_up.png");
    }

    auto& tat = Transforms[{ first, second }];
    this->GetComponent<TextureComponent>().Texture = Images[tat.TextureIndex];
    this->GetComponent<TransformComponent>().Rotation = tat.Rotation * glm::pi<float>() * 0.5f;
}

struct TurningPoint {
    uint32_t Index;
    Directions Directions;
};

std::vector<TurningPoint> TurningPoints;

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
    Blocks[0].Velocity = Direction;
    Blocks[0].SetPosition(Head);

    uint32_t turning_index = 0;
    for(uint32_t i = Size - 1; i > 0; i--)
    {
        Block& curr = Blocks[i];
        Block& next = Blocks[i - 1];

        if(curr.Velocity == next.Velocity)
            curr.SetPosition(curr.GetPosition() + Speed * BlockSize * curr.Velocity);
        else
        {
            TurningPoints.push_back({
                i, { curr.GetPosition() - Blocks[i + 1].GetPosition(), next.GetPosition() - curr.GetPosition() }
            });
        }
    }

    for(auto& turn : TurningPoints)
    {
        // Blocks[turn.Index + 1]
    }
}

void Snake::Render()
{
    for(Block& block : Blocks)
        Renderer2D::DrawQuad(block.GetImage(), block.GetPosition(), glm::vec2(BlockSize));
}