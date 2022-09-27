#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Core/Input.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

using namespace Saddle;

class App : public Application {

Vertex vertices[4] = 
{
    {  -0.5f, -0.5f, glm::vec3(1.f, 0.f, 0.f) },
    {  0.5f, -0.5f,  glm::vec3(0.f, 1.f, 0.f) },
    {  0.5f,  0.5f,  glm::vec3(0.f, 0.f, 1.f) },
    {  -0.5f,  0.5f, glm::vec3(1.f, 0.f, 0.f) },
};

unsigned int indices[6] = {
    0, 1, 2,
    2, 3, 0
};

public:
    void Run()
    {
        int width, height;
        glfwGetFramebufferSize(m_Window.GetNativeWindow(), &width, &height);
        float ratio = width / (float)height;

        Shader vertex_shader("Sandbox/assets/shaders/vertex_shader.glsl", ShaderType::VertexShader);
        Shader fragment_shader("Sandbox/assets/shaders/fragment_shader.glsl", ShaderType::FragmentShader);
        
        VertexBuffer vertex_buffer(4, vertices);
        IndexBuffer index_buffer(6, indices);
        
        Renderer::BindShader(vertex_shader, fragment_shader);
        GLint mvp_location = glGetUniformLocation(Renderer::GetRendererID(), "MVP");

        vertex_buffer.Bind();
        glm::mat4 mvp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

        while(m_Window.IsOpen())
        {
            Renderer::Clear();
            
            Renderer::Submit(vertex_buffer, index_buffer);
            Renderer::Render();

            EventSystem::PollEvents();
        }
    }
};

int main()
{
    Application::Init();

    App app;
    app.Run();

    Application::Close();
}