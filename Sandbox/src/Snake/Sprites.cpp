#include "Sprites.h"

#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Core/Input.h>

Snake::Snake(Scene& scene, InputMode mode)
    : Entity(scene), Mode(mode) { }

void Snake::Update(TimeStep ts)
{
    glm::vec2 dir = GameInput::GetInput(this->Mode);

    
}

void Snake::Render()
{
    for(Block& block : m_Blocks)
        Renderer2D::DrawEntity(block);
}

glm::vec2 GameInput::GetInputKeys()
{
    float x = 0.0f, y = 0.0f;

    x = Input::KeyPressed(Key::Left) ? -1.0f : Input::KeyPressed(Key::Right) ? 1.0f : 0.0f;
    y = Input::KeyPressed(Key::Down) ? -1.0f : Input::KeyPressed(Key::Up) ? 1.0f : 0.0f;

    return { x, y };
}

glm::vec2 GameInput::GetInputWASD()
{
    float x = 0.0f, y = 0.0f;

    x = Input::KeyPressed(Key::A) ? -1.0f : Input::KeyPressed(Key::D) ? 1.0f : 0.0f;
    y = Input::KeyPressed(Key::S) ? -1.0f : Input::KeyPressed(Key::W) ? 1.0f : 0.0f;

    return { x, y };
}