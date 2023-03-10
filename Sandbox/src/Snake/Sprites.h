#pragma once

#include <vector>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

#include "Input.h"

struct Block : public Entity {
    glm::vec2 Velocity;

    Block(const glm::vec2& pos = { 0.0f, 0.0f }, const glm::vec2& v = { 1.0f, 0.0f })
        : Entity(), Velocity(v)
    {
        AddComponent<TextureComponent>("Sandbox/assets/images/block_straight.png");
        AddComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f);
    }
    ~Block() = default;

    glm::vec2 GetPosition() { return glm::vec2(GetComponent<TransformComponent>().Translation); }
    Texture2D* GetImage() { return GetComponent<TextureComponent>().Texture; }

    void SetImage(Texture2D* texture, float rotation)
    {
        GetComponent<TextureComponent>().Texture = texture;
        GetComponent<TransformComponent>().Rotation = glm::vec3(0.0f, 0.0f, rotation);
    }
    void SetPosition(const glm::vec2& pos) { GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }
};

struct Apple : public Entity {
    Apple(const glm::vec2& position = glm::vec2(0.0f, 0.0f))
        : Entity()
    {
        this->AddComponent<TextureComponent>("Sandbox/assets/images/apple.png");
        this->AddComponent<TransformComponent>().Translation = glm::vec3(position, 0.0f);
    }
    ~Apple() = default;

    Texture2D* GetTexture() { return this->GetComponent<TextureComponent>().Texture; }
    glm::vec2 GetPosition() { return glm::vec2(this->GetComponent<TransformComponent>().Translation); }

    void SetPosition(const glm::vec2& pos) { this->GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }
};

class Snake : public Entity {
public:
    const InputMode Mode;
    const float BlockSize;
    const std::string Name;

    uint32_t Size;
    uint32_t Score;
    float Speed;
    glm::vec2 Head;
    glm::vec2 Direction;

public:
    Snake(InputMode mode, float block_size, const std::string& name);
    ~Snake() = default;

    void Update(TimeStep ts);
    void Render();
    void Reset(const glm::vec2& head = { 0.0f, 0.0f }, const glm::vec2& dir = { 1.0f, 0.0f, }, float speed = 1.0f);
    void Increment();

private:
    uint32_t m_Index;
    std::vector<Block> m_Blocks;
};