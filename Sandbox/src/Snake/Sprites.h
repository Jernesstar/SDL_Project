#pragma once

#include <vector>
#include <unordered_map>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

#include "Input.h"

void InitSprites();

struct Block : public Entity {
    glm::vec2 Velocity;

    Block(const glm::vec2& pos = { 0.0f, 0.0f }, const glm::vec2& v = { 1.0f, 0.0f }, uint32_t image_index = 0)
        : Entity(), Velocity(v)
    {
        AddComponent<TextureComponent>().Texture;
        AddComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f);

        SetImage({ }, { });
    }
    ~Block() = default;

    glm::vec2 GetPosition() { return glm::vec2(GetComponent<TransformComponent>().Translation); }
    Texture2D* GetImage() { return GetComponent<TextureComponent>().Texture; }

    void SetImage(glm::vec2 first, glm::vec2 second);
    void SetPosition(const glm::vec2& pos) { GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }
};

struct Apple : public Entity {
    Apple(const glm::vec2& position = glm::vec2(0.0f, 0.0f));
    ~Apple() = default;

    Texture2D* GetImage() { return this->GetComponent<TextureComponent>().Texture; }
    glm::vec2 GetPosition() { return glm::vec2(this->GetComponent<TransformComponent>().Translation); }

    void SetPosition(const glm::vec2& pos) { this->GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }
};

class Snake : public Entity {
public:
    const InputMode Mode;
    const uint32_t BlockSize;
    const std::string Name;

    uint32_t Size;
    uint32_t Score;
    float Speed;

    glm::vec2 Head;
    glm::vec2 Direction;
    std::vector<Block> Blocks;

public:
    Snake(InputMode mode, uint32_t block_size, const std::string& name);
    ~Snake() = default;

    void Update(TimeStep ts);
    void Render();
    void Reset(const glm::vec2& head = { 0.0f, 0.0f }, const glm::vec2& dir = { 1.0f, 0.0f, }, float speed = 1.0f, uint32_t size = 3);
    void Increment();
};