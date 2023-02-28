#pragma once

#include <vector>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

enum class InputMode { Keys, WASD };

class GameInput {
public:
    static glm::vec2 GetInputKeys();
    static glm::vec2 GetInputWASD();
    static glm::vec2 GetInput(InputMode mode) { return mode == InputMode::Keys ? GetInputKeys() : GetInputWASD(); }
};

struct Block : public Entity {
    Block(Scene& scene)
        : Entity(scene)
    { 
        this->AddComponent<TextureComponent>();
        this->AddComponent<TransformComponent>();
    }
    ~Block() = default;

    void SetImage(Texture2D* texture, float rotation)
    {
        this->GetComponent<TextureComponent>().Texture = texture;
        this->GetComponent<TransformComponent>().Rotation = glm::vec3(0.0f, 0.0f, rotation);
    }
};

struct Apple : public Entity {
    glm::vec2 Position{ 0.0f };

    Apple(Scene& scene) : Entity(scene)
    {
        this->AddComponent<TextureComponent>("Sandbox/assets/images/apple.gif");
    }

    ~Apple() = default;
};

class Snake : public Entity {
public:
    const InputMode Mode;

public:
    Snake(Scene& scene, InputMode mode);
    ~Snake() = default;

    void Update(TimeStep ts);
    void Render();

private:
    uint32_t m_Size;
    std::vector<Block> m_Blocks;
};