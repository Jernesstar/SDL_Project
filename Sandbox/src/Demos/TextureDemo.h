#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Core/Input.h>
#include <Saddle/ECS/Entity.h>
#include <Saddle/ECS/ComponentManager.h>
#include <Saddle/Scene/Scene.h>
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

class TextureDemo : public Application {
public:
    TextureDemo();

    void OnUpdate(TimeStep ts);

private:
    struct Vertex {
        glm::vec2 Position;
        glm::vec2 TextureCoordinate;
    };

    const Vertex vertices[4] = 
    {
        { glm::vec2(-0.5f,  0.5f), glm::vec2(0.f, 1.f) }, // Top left, 0
        { glm::vec2( 0.5f,  0.5f), glm::vec2(1.f, 1.f) }, // Top right, 1
        { glm::vec2(-0.5f, -0.5f), glm::vec2(0.f, 0.0) }, // Bottom left, 2
        { glm::vec2( 0.5f, -0.5f), glm::vec2(1.f, 0.0) }, // Bottom right, 3
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
    Texture2D texture{ "Sandbox/assets/images/kick_drum.png" };
    Shader shader{ "Sandbox/assets/shaders/texture.glsl.vert", "Sandbox/assets/shaders/texture.glsl.frag" };

    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };
    glm::mat4 model{ 1.0f };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
    OrthographicCameraController controller{ camera };
};

TextureDemo::TextureDemo()
{
    this->Window.SetWindowIcon("Sandbox/assets/images/start_bg.png");

    texture.Bind(0);
    shader.Bind();
    shader.SetUniformInt("u_Texture", texture);

    EventSystem::RegisterEventListener<ApplicationUpdatedEvent>(
    [this](const ApplicationUpdatedEvent& event) {
        this->OnUpdate(event.DeltaTime);
    });
}

void TextureDemo::OnUpdate(TimeStep ts)
{
    model = glm::rotate(model, glm::pi<float>() / 6.0f, { 0, 0, 1 });

    shader.SetUniformMatrix4("u_ModelMatrix", model);
    shader.SetUniformMatrix4("u_ViewMatrix", camera.GetViewMatrix());
    shader.SetUniformMatrix4("u_ProjMatrix", camera.GetProjectionMatrix());

    Renderer::Clear({ 1, 1, 1, 1 });
    Renderer::Submit(vertex_array);
}