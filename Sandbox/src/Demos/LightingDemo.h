#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

#include <Saddle/Core/Application.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

class LightingDemo : public Application {
public:
    LightingDemo();

    void OnUpdate(TimeStep ts);

private:
    struct Vertex {
        glm::vec3 Position;
    };

    Vertex vertices[8] = 
    {
        { { -0.5f,  0.5f,  0.5 } }, // 0 Front Top Left
        { {  0.5f,  0.5f,  0.5 } }, // 1 Front Top Right
        { { -0.5f, -0.5f,  0.5 } }, // 2 Front Bottom Left
        { {  0.5f, -0.5f,  0.5 } }, // 3 Front Bottom Right

        { { -0.5f,  0.5f, -0.5 } }, // 4 Back Top Left 
        { {  0.5f,  0.5f, -0.5 } }, // 5 Back Top Right
        { { -0.5f, -0.5f, -0.5 } }, // 6 Back Bottom Left
        { {  0.5f, -0.5f, -0.5 } }, // 7 Back Bottom Right
    };

    uint32_t indices[36] =
    {
        0, 2, 3,
        3, 1, 0,

        5, 7, 6,
        6, 4, 5,

        4, 6, 2,
        2, 0, 4,

        1, 3, 7,
        7, 5, 1,

        4, 0, 1,
        1, 5, 4,

        7, 3, 2,
        2, 6, 7,
    };

    BufferLayout layout =
    {
        { "a_VertexPosition", BufferDataType::Vec3, true },
    };

    IndexBuffer* index_buffer = new IndexBuffer(indices);

    VertexBuffer* cube = new VertexBuffer(vertices, layout);
    VertexArray* cube_araay = new VertexArray(cube, index_buffer);

    VertexBuffer* light = new VertexBuffer(vertices, layout);
    VertexArray* light_array = new VertexArray(light, index_buffer);

    Shader shader{ "Sandbox/assets/shaders/Lighting.glsl.vert", "Sandbox/assets/shaders/Lighting.glsl.frag" };

    glm::mat4 cube_model{ 1.0f };
    glm::mat4 light_model{ 1.0f };
    glm::vec3 light_pos = glm::vec3(1.2f, 1.0f, 2.0f), light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 cube_pos = glm::vec3(0.0f, 0.0f, 0.0f), cube_color = glm::vec3(1.0f, 0.5f, 0.31f);

    StereographicCamera camera2{ 90.0f, 0.01f, 100.0f, 1600, 900 };
    CameraController controller{ camera2 };
};

LightingDemo::LightingDemo()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event)
    {
        if(event.Key == Key::Escape)
            Application::Close();
    });
    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [this](const WindowResizedEvent& event)
    {
        this->camera2.Resize(event.Width, event.Height);
    });

    camera2.SetPosition({ 0.0f, 0.0f, 3.0f });
    controller.RotationSpeed = 1.0f;

    light_model = glm::translate(light_model, light_pos);
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    shader.Bind();
    shader.SetUniformVec3("u_LightColor", light_color);
    shader.SetUniformVec3("u_ObjectColor", cube_color);
}

void LightingDemo::OnUpdate(TimeStep ts)
{
    controller.OnUpdate(ts);
    shader.SetUniformMatrix4("u_ViewProj", camera2.GetViewProjection());

    Renderer::Clear({ 0.f, 0.f, 0.f, 0.f });

    shader.SetUniformMatrix4("u_Model", cube_model);
    shader.SetUniformVec3("u_LightColor", light_color);
    shader.SetUniformVec3("u_ObjectColor", cube_color);
    Renderer::DrawIndexed(cube_araay);

    shader.SetUniformMatrix4("u_Model", light_model);
    shader.SetUniformVec3("u_LightColor", light_color);
    shader.SetUniformVec3("u_ObjectColor", light_color);
    Renderer::DrawIndexed(light_array);
}