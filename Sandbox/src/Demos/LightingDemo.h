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

    BufferLayout l3 =
    {
        { "Position", BufferDataType::Vec3 },
        { "Ambient",  BufferDataType::Vec3 },
        { "Diffuse",  BufferDataType::Vec3 },
        { "Specular", BufferDataType::Vec3 },
    };

    UniformBuffer uniform_buffer{ l3, 1 };

    IndexBuffer* index_buffer = new IndexBuffer(indices);

    VertexBuffer* light_buffer = new VertexBuffer(vertices, l1);
    VertexArray* light_array = new VertexArray(light_buffer, index_buffer);

    VertexBuffer* cube_buffer = new VertexBuffer(cube_vertices, l2);
    VertexArray* cube_array = new VertexArray(cube_buffer, nullptr);

    Shader light_shader{
        { ShaderType::VertexShader, "Sandbox/assets/shaders/Light.glsl.vert" },
        { ShaderType::FragmentShader, "Sandbox/assets/shaders/Light.glsl.frag" } 
    };
    Shader cube_shader{
        { ShaderType::VertexShader, "Sandbox/assets/shaders/Lighting.glsl.vert" },
        { ShaderType::FragmentShader, "Sandbox/assets/shaders/Lighting.glsl.frag" } 
    };

    Texture2D wood{ "Sandbox/assets/images/wood.png" };
    Texture2D wood_specular{ "Sandbox/assets/images/wood_specular.png" };

    glm::mat4 light_model{ 1.0f };
    glm::mat4 cube_model{ 1.0f };
    glm::vec3 light_position = { 1.2f, 1.0f, 2.0f }, light_color = { 1.0f, 1.0f, 1.0f };
    glm::vec3 cube_position = { 0.0f, 0.0f, 0.0f };

    glm::vec3 light_ambient = { 0.2f, 0.2f, 0.2f };
    glm::vec3 light_diffuse = { 0.5f, 0.5f, 0.5f };
    glm::vec3 light_specular = { 1.0f, 1.0f, 1.0f };

    float shininess = 32.0f;

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

    light_model = glm::translate(light_model, light_position);
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    cube_shader.Bind();
    cube_shader.SetUniformMatrix4("u_Model", cube_model);

    wood.Bind(0);
    wood_specular.Bind(1);
    cube_shader.SetUniformInt("u_Material.Diffuse", 0);
    cube_shader.SetUniformInt("u_Material.Specular", 1);

    light_shader.Bind();
    light_shader.SetUniformMatrix4("u_Model", light_model);
    light_shader.SetUniformVec3("u_LightColor", light_color);

    glDisable(GL_CULL_FACE);
}

void LightingDemo::OnUpdate(TimeStep ts)
{
    controller.OnUpdate(ts);

    glm::vec3 pos = light_position;

    ImGui::Begin("Material");
    {
        ImGui::SliderFloat("Material.Shininess", &shininess, 0.0f, 512.0f);
    }
    ImGui::End();

    ImGui::Begin("Light");
    {
        ImGui::ColorEdit3("Light.Position", glm::value_ptr(pos));
        ImGui::ColorEdit3("Light.Ambient",  glm::value_ptr(light_ambient));
        ImGui::ColorEdit3("Light.Diffuse",  glm::value_ptr(light_diffuse));
        ImGui::ColorEdit3("Light.Specular", glm::value_ptr(light_specular));
    }
    ImGui::End();

    Renderer::Clear({ 0.f, 0.f, 0.f, 0.f });

    light_shader.Bind();
    light_shader.SetUniformMatrix4("u_ViewProj", camera.GetViewProjection());

    if(light_position != pos)
    {
        light_position = pos;
        light_model = glm::translate(light_model, light_position);
        light_shader.SetUniformMatrix4("u_Model", light_model);
        uniform_buffer.SetData("Position", &light_position);
    }

    Renderer::DrawIndexed(light_array);

    cube_shader.Bind();
    cube_shader.SetUniformFloat("u_Material.Shininess", shininess);

    uniform_buffer.SetData("Ambient",  &light_ambient);
    uniform_buffer.SetData("Diffuse",  &light_diffuse);
    uniform_buffer.SetData("Specular", &light_specular);

    cube_shader.SetUniformMatrix4("u_ViewProj", camera.GetViewProjection());
    cube_shader.SetUniformVec3("u_CameraPosition", camera.GetPosition());
    cube_array->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}