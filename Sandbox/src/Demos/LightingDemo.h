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
    struct Vertex1 {
        glm::vec3 Position;
    };
    struct Vertex2 {
        glm::vec3 Position;
        glm::vec3 Normal;
    };

    Vertex1 vertices[8] = 
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

    Vertex2 cube_vertices[6 * 6] =
    {
        { { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },

        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        { {  0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        { {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        { {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        { { -0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f } },
        { { -0.5f, -0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f } },

        { { 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f } },

        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f } },
        { { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f } },

        { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } }
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

    BufferLayout l1 =
    {
        { "a_Position", BufferDataType::Vec3, true },
    };

    BufferLayout l2 =
    {
        { "a_Position", BufferDataType::Vec3, true },
        { "a_Normal",   BufferDataType::Vec3, true },
    };

    IndexBuffer* index_buffer = new IndexBuffer(indices);

    VertexBuffer* light_buffer = new VertexBuffer(vertices, l1);
    VertexArray* light_array = new VertexArray(light_buffer, index_buffer);

    VertexBuffer* cube_buffer = new VertexBuffer(cube_vertices, l2);
    VertexArray* cube_array = new VertexArray(cube_buffer, nullptr);

    Shader light_shader{ "Sandbox/assets/shaders/Light.glsl.vert", "Sandbox/assets/shaders/Light.glsl.frag" };
    Shader cube_shader{ "Sandbox/assets/shaders/Lighting.glsl.vert", "Sandbox/assets/shaders/Lighting.glsl.frag" };

    glm::mat4 light_model{ 1.0f };
    glm::mat4 cube_model{ 1.0f };
    glm::vec3 light_pos = glm::vec3(1.2f, 1.0f, 2.0f), light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 cube_pos = glm::vec3(0.0f, 0.0f, 0.0f), cube_color = glm::vec3(1.0f, 0.5f, 0.31f);

    StereographicCamera camera{ 75.0f, 0.01f, 100.0f, 1600, 900 };
    CameraController controller{ camera };
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
        this->camera.Resize(event.Width, event.Height);
    });

    camera.SetPosition({ 0.0f, 0.0f, 4.0f });
    controller.RotationSpeed = 1.0f;

    light_model = glm::translate(light_model, light_pos);
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    cube_shader.Bind();
    cube_shader.SetUniformVec3("u_LightColor", light_color);
    cube_shader.SetUniformVec3("u_ObjectColor", cube_color);
    cube_shader.SetUniformVec3("u_LightPosition", light_pos);
    cube_shader.SetUniformMatrix4("u_Model", cube_model);

    light_shader.Bind();
    light_shader.SetUniformVec3("u_LightColor", light_color);
    light_shader.SetUniformMatrix4("u_Model", light_model);

    glDisable(GL_CULL_FACE);
}

void LightingDemo::OnUpdate(TimeStep ts)
{
    controller.OnUpdate(ts);

    Renderer::Clear({ 0.f, 0.f, 0.f, 0.f });

    light_shader.Bind();
    light_shader.SetUniformMatrix4("u_ViewProj", camera.GetViewProjection());
    Renderer::DrawIndexed(light_array);

    cube_shader.Bind();
    cube_shader.SetUniformMatrix4("u_ViewProj", camera.GetViewProjection());
    cube_array->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}