#pragma once

#include <imgui/imgui.h>

#include <Saddle/Core/Application.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>

#include <OpenGL/Shader.h>
#include <OpenGL/UniformBuffer.h>

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
        glm::vec2 TextureCoordinates;
    };

    // struct Light {
    //     glm::vec3 Position;
    //     glm::vec3 Ambient;
    //     glm::vec3 Diffuse;
    //     glm::vec3 Specular;
    // };

    struct PointLight {
        glm::vec3 Position;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;

        float Constant;
        float Linear;
        float Quadratic;
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
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },

        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { {  0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },

        { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -0.5f, -0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },

        { { 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },

        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },

        { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }
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
        { "a_Position", BufferDataType::Vec3 },
    };

    BufferLayout l2 =
    {
        { "a_Position", BufferDataType::Vec3 },
        { "a_Normal",   BufferDataType::Vec3 },
        { "a_TextureCoordinate",   BufferDataType::Vec2 },
    };

    IndexBuffer* index_buffer = new IndexBuffer(indices);

    VertexBuffer* light_buffer = new VertexBuffer(vertices, l1);
    VertexArray* light_array = new VertexArray(light_buffer, index_buffer);

    VertexBuffer* cube_buffer = new VertexBuffer(cube_vertices, l2);
    VertexArray* cube_array = new VertexArray(cube_buffer, nullptr);

    Shader light_shader{
        { "Sandbox/assets/shaders/Light.glsl.vert", ShaderType::Vertex },
        { "Sandbox/assets/shaders/Light.glsl.frag", ShaderType::Fragment } 
    };
    Shader cube_shader{
        { "Sandbox/assets/shaders/Lighting.glsl.vert", ShaderType::Vertex },
        { "Sandbox/assets/shaders/Lighting.glsl.frag", ShaderType::Fragment } 
    };

    Texture2D wood{ "Sandbox/assets/images/wood.png" };
    Texture2D wood_specular{ "Sandbox/assets/images/wood_specular.png" };

    glm::mat4 light_model{ 1.0f };
    glm::mat4 cube_model{ 1.0f };
    glm::vec3 cube_position = { 0.0f, 0.0f, 0.0f };

    // Light light;
    PointLight light;
    float shininess = 32.0f;

    glm::mat4 cube_positions[10] =
    {
        glm::rotate(glm::translate(glm::mat4(1.0f), {  0.0f,  0.0f,  0.0f }), glm::radians(20.0f * 0.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), {  2.0f,  5.0f, -9.0f }), glm::radians(20.0f * 1.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), { -1.5f, -2.2f, -2.5f }), glm::radians(20.0f * 2.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), { -3.8f, -2.0f, -9.3f }), glm::radians(20.0f * 3.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), {  2.4f, -0.4f, -3.5f }), glm::radians(20.0f * 4.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), { -1.7f,  3.0f, -7.5f }), glm::radians(20.0f * 5.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), {  1.3f, -2.0f, -2.5f }), glm::radians(20.0f * 6.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), {  1.5f,  2.0f, -2.5f }), glm::radians(20.0f * 7.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), {  1.5f,  0.2f, -1.5f }), glm::radians(20.0f * 8.0f), { 1.0f, 0.3f, 0.5f }),
        glm::rotate(glm::translate(glm::mat4(1.0f), { -1.3f,  1.0f, -1.5f }), glm::radians(20.0f * 9.0f), { 1.0f, 0.3f, 0.5f }),
    };

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

    light.Position = { 1.2f, 1.0f, 2.0f };
    light.Ambient  = { 0.2f, 0.2f, 0.2f };
    light.Diffuse  = { 0.5f, 0.5f, 0.5f };
    light.Specular = { 1.0f, 1.0f, 1.0f };
    light.Constant  = 1.0f;
    light.Linear    = 0.09f;
    light.Quadratic = 0.032f;

    light_model = glm::translate(light_model, light.Position);
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    light_shader.Bind();
    light_shader.SetMat4("u_Model", light_model);
    light_shader.SetVec3("u_LightColor", { 1.0f, 1.0f, 1.0f });

    cube_shader.Bind();
    cube_shader.SetMat4("u_Model", cube_model);
    cube_shader.SetVec3("u_Light.Position", light.Position);

    cube_shader.SetInt("u_Material.Diffuse", 0);
    cube_shader.SetInt("u_Material.Specular", 1);
    cube_shader.SetFloat("u_Material.Shininess", 32.0f);

    wood.Bind(0);
    wood_specular.Bind(1);

    glDisable(GL_CULL_FACE);
}

void LightingDemo::OnUpdate(TimeStep ts)
{
    controller.OnUpdate(ts);

    ImGui::Begin("Light");
    {
        ImGui::ColorEdit3("Light.Ambient",  glm::value_ptr(light.Ambient));
        ImGui::ColorEdit3("Light.Diffuse",  glm::value_ptr(light.Diffuse));
        ImGui::ColorEdit3("Light.Specular", glm::value_ptr(light.Specular));

        ImGui::SliderFloat("Light.Constant",  &light.Constant,  0.0f, 1.0f);
        ImGui::SliderFloat("Light.Linear",    &light.Linear,    0.0f, 1.0f);
        ImGui::SliderFloat("Light.Quadratic", &light.Quadratic, 0.0f, 1.0f);
    }
    ImGui::End();

    Renderer::Clear({ 0.0f, 0.0f, 0.0f, 0.0f });

    light_shader.Bind();
    light_shader.SetMat4("u_ViewProj", camera.GetViewProjection());
    Renderer::DrawIndexed(light_array);

    cube_shader.Bind();
    cube_shader.SetVec3("u_CameraPosition", camera.GetPosition());
    cube_shader.SetMat4("u_ViewProj", camera.GetViewProjection());

    cube_shader.SetVec3("u_Light.Ambient",  light.Ambient);
    cube_shader.SetVec3("u_Light.Diffuse",  light.Diffuse);
    cube_shader.SetVec3("u_Light.Specular", light.Specular);

    cube_shader.SetFloat("u_Light.Constant",  light.Constant);
    cube_shader.SetFloat("u_Light.Linear",    light.Linear);
    cube_shader.SetFloat("u_Light.Quadratic", light.Quadratic);

    cube_array->Bind();
    for(uint32_t i = 0; i < 10; i++)
    {
        cube_shader.SetMat4("u_Model", cube_positions[i]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}