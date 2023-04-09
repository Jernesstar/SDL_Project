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

class Cube3D : public Application {
public:
    Cube3D();

    void OnUpdate(TimeStep ts);

private:
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
    };

    Vertex vertices[8] = 
    {
        { glm::vec3(-0.5f,  0.5f,  0.5), glm::vec3(0.f, 1.f, 0.f) }, // 0 Front Top Left
        { glm::vec3( 0.5f,  0.5f,  0.5), glm::vec3(1.f, 0.f, 1.f) }, // 1 Front Top Right
        { glm::vec3(-0.5f, -0.5f,  0.5), glm::vec3(0.f, 1.f, 0.f) }, // 2 Front Bottom Left
        { glm::vec3( 0.5f, -0.5f,  0.5), glm::vec3(1.f, 0.f, 1.f) }, // 3 Front Bottom Right

        { glm::vec3(-0.5f,  0.5f, -0.5), glm::vec3(0.f, 1.f, 0.f) }, // 4 Back Top Left 
        { glm::vec3( 0.5f,  0.5f, -0.5), glm::vec3(1.f, 0.f, 0.f) }, // 5 Back Top Right
        { glm::vec3(-0.5f, -0.5f, -0.5), glm::vec3(1.f, 0.f, 0.f) }, // 6 Back Bottom Left
        { glm::vec3( 0.5f, -0.5f, -0.5), glm::vec3(0.f, 1.f, 1.f) }, // 7 Back Bottom Right
    };

    uint32_t indices[36] =
    {
        3, 2, 0, // Front face
        0, 1, 3,

        6, 7, 5, // Back face
        5, 4, 6,

        2, 6, 4, // Left face
        4, 0, 2,

        7, 3, 1, // Right face
        1, 5, 7,

        1, 0, 4, // Top face
        4, 5, 1,

        2, 3, 7, // Bottom face
        7, 6, 2,
    };

    BufferLayout layout =
    {
        { "a_VertexPosition", BufferDataType::Vec3, true },
        { "a_Color", BufferDataType::Vec3, true },
    };

    VertexBuffer* vertex_buffer = new VertexBuffer(vertices, layout);
    IndexBuffer* index_buffer = new IndexBuffer(indices);
    VertexArray* vertex_array = new VertexArray(vertex_buffer, index_buffer);

    Shader shader{ "Sandbox/assets/shaders/3D.glsl.vert", "Sandbox/assets/shaders/3D.glsl.frag" };

    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };
    glm::mat4 model{ 1.0f };

    TransformComponent transform =
    {
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 0.05f, 0.03f, 0.03f }, 
        glm::vec3{ 1.0f, 1.0f, 1.0f }
    };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
    StereographicCamera camera2{ 90.0f, 0.0f, 1.0f, 1600, 900 };
    CameraController controller{ camera2 };
};

Cube3D::Cube3D()
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

    shader.Bind();

    camera2.SetPosition({ 0.0f, 0.0f, 3.0f });
    controller.RotationSpeed = 1.0f;
}

void Cube3D::OnUpdate(TimeStep ts)
{
    ImGui::ShowDemoWindow();
    ImGui::Begin("Vertices");
    {
        for(uint32_t i = 0; i < 8; i++)
        {
            ImGui::PushID(i);
            
            ImGui::ColorEdit3("Vertex", glm::value_ptr(vertices[i].Color));
            ImGui::SliderFloat3("Vertex", glm::value_ptr(vertices[i].Position), -5.0f, 5.0f);

            ImGui::Separator();
            ImGui::PopID();
        }
    }
    ImGui::End();

    vertex_buffer->SetData(vertices);

    model *= transform.GetTransform();
    controller.OnUpdate(ts);

    shader.SetUniformMatrix4("u_ModelMatrix", model);
    shader.SetUniformMatrix4("u_ViewProjMatrix", camera2.GetViewProjection());

    Renderer::Clear({ 0.f, 0.f, 0.f, 0.f });
    Renderer::DrawIndexed(vertex_array);
}