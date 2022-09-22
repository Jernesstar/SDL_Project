#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <OpenGL/Shader.h>

using namespace Saddle;
 
struct
{
    float x, y;
    float r, g, b;
}
vertices[3] = 
{
    {  -0.5f, -0.5f, 1.f, 0.f, 0.f },
    { 0.5f, -0.5f, 0.f, 1.f, 0.f },
    {  0.f,  0.5f, 0.f, 0.f, 1.f }
};

class App : public Application {
public:
    void Run()
    {
        GLFWwindow* window = m_Window.GetNativeWindow();
        GLuint vertex_buffer, program;
        GLint mvp_location, vertex_position, vertex_color;
    
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        Shader vertex_shader("Sandbox/assets/shaders/vertex_shader.glsl", ShaderType::VertexShader);
        Shader fragment_shader("Sandbox/assets/shaders/fragment_shader.glsl", ShaderType::FragmentShader);
        Renderer::Submit(vertex_shader, fragment_shader);
        program = Renderer::GetRendererID();

        mvp_location = glGetUniformLocation(program, "MVP");
        vertex_position = glGetAttribLocation(program, "vPos");
        vertex_color = glGetAttribLocation(program, "vCol");
    
        glEnableVertexAttribArray(vertex_position);
        glVertexAttribPointer(vertex_position, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
        glEnableVertexAttribArray(vertex_color);
        glVertexAttribPointer(vertex_color, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 3));
    
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        while (!glfwWindowShouldClose(window))
        {
            mat4x4 m, p, mvp;
    
            mat4x4_identity(m);
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);
    
            glUseProgram(program);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
    
            glfwSwapBuffers(window);
            EventSystem::PollEvents();

            glClearColor(255, 255, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
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