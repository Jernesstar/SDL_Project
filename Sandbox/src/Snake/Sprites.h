#pragma once

#include <vector>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

#include "Input.h"

struct Block : public Entity {
    Block(Scene* scene, glm::vec2 position)
        : Entity(*scene)
    { 
        this->AddComponent<TextureComponent>("Sandbox/assets/images/block_straight.png");
        this->AddComponent<TransformComponent>().Translation = glm::vec3(position, 0.0f);
    }
    ~Block() = default;

    void SetImage(Texture2D* texture, float rotation)
    {
        this->GetComponent<TextureComponent>().Texture = texture;
        this->GetComponent<TransformComponent>().Rotation = glm::vec3(0.0f, 0.0f, rotation);
    }

    glm::vec3& GetPosition() { return this->GetComponent<TransformComponent>().Translation; }
};

struct Apple : public Entity {
    glm::vec2 Position{ 0.0f };

    Apple(Scene* scene) : Entity(*scene)
    {
        this->AddComponent<TextureComponent>("Sandbox/assets/images/apple.png");
    }

    ~Apple() = default;
};

class Snake : public Entity {
public:
    const InputMode Mode;
    const uint32_t BlockSize;
    const std::string Name;

public:
    Snake(Scene* scene, InputMode mode, uint32_t block_size, const std::string& name);
    ~Snake() = default;

    void Reset();
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
    Scene* m_Scene;
};