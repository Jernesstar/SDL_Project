#pragma once

#include <iostream>

#include <glad/glad.h>

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

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

class TextureDemo : public Application {
public:
    TextureDemo()
    {
        Window.SetWindowIcon("Sandbox/assets/images/start_bg.png");
    }
    void Run() override;

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
        // { glm::vec2(-0.5f,  0.0f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle left, 4
        // { glm::vec2( 0.0f,  0.5f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle top, 5
    };

    unsigned int indices[6] = {
        0, 2, 3,
        0, 1, 3
    };

    BufferLayout layout = {
        { "a_VertexPosition", BufferDataType::Vec2, true },
        { "a_TextureCoordinate", BufferDataType::Vec2, true },
    };

    VertexArray vertex_array{ vertices, layout, indices };

    Texture2D texture{ "Sandbox/assets/images/kick_drum.png" };
    Shader shader{ "Sandbox/assets/shaders/vertex_texture.glsl", "Sandbox/assets/shaders/fragment_texture.glsl" };

};

void TextureDemo::Run()
{
    texture.Bind(0);

    shader.Bind();
    shader.SetUniformInt("u_Texture", texture);

    auto vec = Window.GetFrameBufferSize();
    float ratio = vec.x / vec.y;

    glm::mat4 model(1), view(1), proj, mvp;
    proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

    while(Window.IsOpen())
    {
        Renderer::Clear({ 1, 1, 1, 1 });

        model = glm::rotate(model, glm::pi<float>() / 6.0f, { 0, 0, 1 });

        shader.SetUniformMatrix4("u_ModelMatrix", model);
        shader.SetUniformMatrix4("u_ViewMatrix", view);
        shader.SetUniformMatrix4("u_ProjMatrix", proj);

        Renderer::Submit(vertex_array, shader);
        Renderer::Render();

        EventSystem::PollEvents();
    }

}