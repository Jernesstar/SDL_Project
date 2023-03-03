#pragma once

#include <vector>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

#include "Input.h"

struct Block : public Entity {
    Block() : Entity()
    { 
        this->AddComponent<TextureComponent>("Sandbox/assets/images/block_straight.png");
        this->AddComponent<TransformComponent>();
    }
    ~Block() = default;

    void SetImage(Texture2D* texture, float rotation)
    {
        this->GetComponent<TextureComponent>().Texture = texture;
        this->GetComponent<TransformComponent>().Rotation = glm::vec3(0.0f, 0.0f, rotation);
    }

    glm::vec2 GetPosition() { return glm::vec2(this->GetComponent<TransformComponent>().Translation); }
    void SetPosition(const glm::vec2& pos) { this->GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }

    Texture2D* GetTexture() { return this->GetComponent<TextureComponent>().Texture; }
};

struct Apple : public Entity {
    Apple() : Entity()
    {
        this->AddComponent<TextureComponent>("Sandbox/assets/images/apple.png");
        this->AddComponent<TransformComponent>();
    }
    ~Apple() = default;

    glm::vec2 GetPosition() { return glm::vec2(this->GetComponent<TransformComponent>().Translation); }
    void SetPosition(const glm::vec2& pos) { this->GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }

    Texture2D* GetTexture() { return this->GetComponent<TextureComponent>().Texture; }
};

class Snake : public Entity {
public:
    const InputMode Mode;
    const uint32_t BlockSize;
    const std::string Name;

public:
    Snake(InputMode mode, uint32_t block_size, const std::string& name);
    ~Snake() = default;

    void Reset(const glm::vec2& head_position, const glm::vec2& direction);
    void Update(TimeStep ts);

    void Increment()
    {
        m_Size++;
        m_Score++;
    }

    void Render();

private:
    uint32_t m_Size;
    uint32_t m_Score;
    std::vector<Block> m_Blocks;
};