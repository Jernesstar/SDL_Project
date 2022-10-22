#pragma once

#include <iostream>

#include <glad/glad.h>

#include <glm/vec3.hpp>
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

class Demo3D : public Application {
public:
    void Run() override;
};

void Demo3D::Run()
{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
    };

    const Vertex vertices[8] = 
    {
        { glm::vec3(-0.5f,  0.5f, 0.5), glm::vec3(0.f, 1.f, 0.f) }, // 0 Front Top Left
        { glm::vec3( 0.5f,  0.5f, 0.5), glm::vec3(1.f, 1.f, 1.f) }, // 1 Front Top Right
        { glm::vec3(-0.5f, -0.5f, 0.5), glm::vec3(0.f, 0.f, 0.f) }, // 2 Front Bottom Left
        { glm::vec3( 0.5f, -0.5f, 0.5), glm::vec3(1.f, 0.f, 0.f) }, // 3 Front Bottom Right

        { glm::vec3(-0.5f,  0.5f, -0.5), glm::vec3(0.f, 1.f, 0.f) }, // 4 Back Top Left 
        { glm::vec3( 0.5f,  0.5f, -0.5), glm::vec3(1.f, 1.f, 1.f) }, // 5 Back Top Right
        { glm::vec3(-0.5f, -0.5f, -0.5), glm::vec3(0.f, 0.f, 0.f) }, // 6 Back Bottom Left
        { glm::vec3( 0.5f, -0.5f, -0.5), glm::vec3(1.f, 0.f, 0.f) }, // 7 Back Bottom Right
    };

    unsigned int indices[36] = {

        0, 2, 3,
        0, 1, 3,

        0 + 1, 2 + 1, 3 + 1,
        0 + 1, 1 + 1, 3 + 1,

        0 + 2, 2 + 2, 3 + 2,
        0 + 2, 1 + 2, 3 + 2,

        0 + 3, 2 + 3, 3 + 3,
        0 + 3, 1 + 3, 3 + 3,

        0 + 4, 2 + 4, 3 + 4,
        0 + 4, 1 + 4, 3 + 4,

        0 + 5, 2 + 5, 0,
        0 + 5, 1 + 5, 0,
    };

    BufferLayout layout({
        { "a_VertexPosition", BufferDataType::Vec3, true },
        { "a_Color", BufferDataType::Vec3, true },
    });

    VertexArray vertex_array(vertices, layout, indices);

    Shader shader("Sandbox/assets/shaders/vertex_3D.glsl", 
        "Sandbox/assets/shaders/fragment_3D.glsl");

    shader.Bind();

    auto vec = Window.GetFrameBufferSize();
    float ratio = vec.x / vec.y;

    glm::mat4 mvp, model(1), view(1), proj;
    proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

    while(Window.IsOpen())
    {
        Renderer::Clear({ 1, 1, 1, 1 });

        shader.SetUniformMatrix4("u_ModelMatrix", model);
        shader.SetUniformMatrix4("u_ViewMatrix", view);
        shader.SetUniformMatrix4("u_ProjMatrix", proj);

        Renderer::Submit(vertex_array, shader);
        Renderer::Render();

        EventSystem::PollEvents();
    }

}