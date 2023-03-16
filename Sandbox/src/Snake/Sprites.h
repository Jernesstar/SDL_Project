#pragma once

#include <vector>
#include <unordered_map>

#include <Saddle/ECS/Entity.h>
#include <OpenGL/Texture2D.h>

#include "Input.h"

struct Block : public Entity {
    glm::vec2 Velocity;

    static void Setup()
    {
        m_Images[0] = new Texture2D("Sandbox/assets/images/block_straight.png");
        m_Images[1] = new Texture2D("Sandbox/assets/images/block_left_up.png");
        m_Images[2] = new Texture2D("Sandbox/assets/images/block_right_up.png");

        m_Transforms[{ LEFT, RIGHT }] = glm::mat4(1.0f);
    }

    Block(const glm::vec2& pos = { 0.0f, 0.0f }, const glm::vec2& v = { 1.0f, 0.0f }, uint32_t image_index = 0)
        : Entity(), Velocity(v)
    {
        AddComponent<TextureComponent>().Texture = m_Images[image_index];
        AddComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f);
    }
    ~Block() = default;

    glm::vec2 GetPosition() { return glm::vec2(GetComponent<TransformComponent>().Translation); }
    Texture2D* GetImage() { return GetComponent<TextureComponent>().Texture; }

    void SetImage(glm::vec2 first, glm::vec2 second)
    {

    }
    void SetPosition(const glm::vec2& pos) { GetComponent<TransformComponent>().Translation = glm::vec3(pos, 0.0f); }

private:
    static std::unordered_map<uint32_t, Texture2D*> m_Images;
    static std::unordered_map<std::pair<glm::vec2, glm::vec2>, glm::mat4> m_Transforms;

    static inline const glm::vec2 LEFT  = { -1.0f,  0.0f };
    static inline const glm::vec2 RIGHT = {  1.0f,  0.0f };
    static inline const glm::vec2 UP    = {  0.0f,  1.0f };
    static inline const glm::vec2 DOWN  = {  0.0f, -1.0f };
};

struct Apple : public Entity {
    Apple(const glm::vec2& position = glm::vec2(0.0f, 0.0f))
        : Entity()
    {
        this->AddComponent<TextureComponent>("Sandbox/assets/images/apple.png");
        this->AddComponent<TransformComponent>().Translation = glm::vec3(position, 0.0f);
    }
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