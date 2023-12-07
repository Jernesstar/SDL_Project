#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

#include <Saddle/Core/Application.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>
#include <OpenGL/Cubemap.h>

using namespace Saddle;

class CubeDemo : public Application {
public:
    CubeDemo();

    void OnUpdate(TimeStep ts);

private:
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
    };

    Vertex vertices[8] = 
    {
        { { -0.5f,  0.5f,  0.5 }, { 0.f, 1.f, 0.f } }, // 0 Front Top Left
        { {  0.5f,  0.5f,  0.5 }, { 1.f, 0.f, 1.f } }, // 1 Front Top Right
        { { -0.5f, -0.5f,  0.5 }, { 0.f, 1.f, 0.f } }, // 2 Front Bottom Left
        { {  0.5f, -0.5f,  0.5 }, { 1.f, 0.f, 1.f } }, // 3 Front Bottom Right

        { { -0.5f,  0.5f, -0.5 }, { 0.f, 1.f, 0.f } }, // 4 Back Top Left 
        { {  0.5f,  0.5f, -0.5 }, { 1.f, 0.f, 0.f } }, // 5 Back Top Right
        { { -0.5f, -0.5f, -0.5 }, { 1.f, 0.f, 0.f } }, // 6 Back Bottom Left
        { {  0.5f, -0.5f, -0.5 }, { 0.f, 1.f, 1.f } }, // 7 Back Bottom Right
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
        { "a_Position", BufferDataType::Vec3, true },
        { "a_Color", BufferDataType::Vec3, true },
    };

    VertexBuffer* vertex_buffer = new VertexBuffer(vertices, layout);
    IndexBuffer* index_buffer = new IndexBuffer(indices);
    VertexArray* vertex_array = new VertexArray(vertex_buffer, index_buffer);

    Shader shader{ { "Sandbox/assets/shaders/Cube.glsl.frag", "Sandbox/assets/shaders/Cube.glsl.vert" } };
    Shader cubemap_shader{ { "Sandbox/assets/shaders/Cubemap.glsl.frag", "Sandbox/assets/shaders/Cubemap.glsl.vert" } };

    Cubemap* skybox = new Cubemap({
        "Sandbox/assets/cubemaps/skybox/right.jpg",
        "Sandbox/assets/cubemaps/skybox/left.jpg",
        "Sandbox/assets/cubemaps/skybox/top.jpg",
        "Sandbox/assets/cubemaps/skybox/bottom.jpg",
        "Sandbox/assets/cubemaps/skybox/front.jpg",
        "Sandbox/assets/cubemaps/skybox/back.jpg",
    });

    glm::ivec2 vec{ GetWindow().GetFrameBufferSize() };
    StereographicCamera camera{ 90.0f, 0.01f, 100.0f, vec.x, vec.y };
    CameraController controller{ camera };
};

CubeDemo::CubeDemo()
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

    camera.SetPosition({ 0.0f, 0.0f, 3.0f });
    controller.RotationSpeed = 1.0f;
}

void CubeDemo::OnUpdate(TimeStep ts)
{
    vertex_buffer->SetData(vertices);

    controller.OnUpdate(ts);

    Renderer::Clear({ 0.f, 0.f, 0.f, 0.f });

    // cubemap_shader.Bind();
    // Renderer::RenderCubemap(skybox);
    
    shader.Bind();
    shader.SetMat4("u_ViewProj", camera.GetViewProjection());
    Renderer::DrawIndexed(vertex_array);
}