#pragma once

#include <Saddle/Core/Application.h>
#include <Saddle/ECS/Entity.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/OrthographicCameraController.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

class Game : public Application {
public:
    Game();
    ~Game() = default;

    void OnUpdate(TimeStep ts) override;

private:
    Scene m_Scene;
    Entity Kick_Drum{ m_Scene };
    Entity Snare_Drum{ m_Scene };

    struct Vertex {
        glm::vec2 Position;
        glm::vec2 TextureCoordinate;
    };

    const Vertex vertices[4] = 
    {
        { glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // Top left, 0
        { glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // Top right, 1
        { glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // Bottom left, 2
        { glm::vec2( 0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // Bottom right, 3
    };

    unsigned int indices[6] =
    {
        3, 2, 0,
        0, 1, 3
    };

    BufferLayout layout =
    {
        { "a_VertexPosition", BufferDataType::Vec2, true },
        { "a_TextureCoordinate", BufferDataType::Vec2, true },
    };

    VertexArray vertex_array{ vertices, layout, indices };
    Shader shader{ "Sandbox/assets/shaders/texture.glsl.vert", "Sandbox/assets/shaders/texture.glsl.frag" };

    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
    OrthographicCameraController controller{ camera };
};