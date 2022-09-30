#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Core/Input.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

using namespace Saddle;

Vertex vertices[6] = 
{
    { glm::vec2(-0.5f, -0.5f), glm::vec4(0.f, 1.f, 1.f, 1.0) }, // Bottom left, 0
    { glm::vec2( 0.5f, -0.5f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Bottom right, 1
    { glm::vec2(-0.5f,  0.5f), glm::vec4(1.f, 0.f, 0.f, 1.0) }, // Top left, 2
    { glm::vec2( 0.5f,  0.5f), glm::vec4(0.f, 1.f, 1.f, 1.0) }, // Top right, 3
    { glm::vec2(-0.5f,  0.0f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle left, 4
    { glm::vec2( 0.0f,  0.5f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle top, 5
};

unsigned int indices[9] = {
    1, 0, 2,
    0, 2, 3,
    4, 2, 5
};

class App : public Application {
public:
    void Run() override
    {
        Shader vertex_shader("Sandbox/assets/shaders/vertex_shader.glsl", ShaderType::VertexShader);
        Shader fragment_shader("Sandbox/assets/shaders/fragment_shader.glsl", ShaderType::FragmentShader);
        
        VertexBuffer vertex_buffer(6, vertices);
        IndexBuffer index_buffer(9, indices);
        
        Renderer::BindShader(vertex_shader, fragment_shader);
        GLint mvp_location = glGetUniformLocation(Renderer::GetRendererID(), "u_MVP");

        vertex_buffer.Bind();

        auto vec = Window.GetFrameBufferSize();
        float ratio = vec.x / vec.y;
        glm::mat4 mvp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        glm::mat4 identity_matrix(1);

        while(Window.IsOpen())
        {
            Renderer::Clear();

            mvp = mvp * glm::translate(identity_matrix, glm::vec3(0.01f, 0.0f, 0.0f));
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        
            Renderer::Submit(vertex_buffer, index_buffer);
            Renderer::Render();

            EventSystem::PollEvents();
        }
    }
};
