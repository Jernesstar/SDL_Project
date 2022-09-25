#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { m_Window = Application::Get().GetWindow().GetNativeWindow(); }

void Renderer::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BindShaders(const Shader& vertex_shader, const Shader& fragment_shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertex_shader);
    glAttachShader(m_RendererID, fragment_shader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
}

void Renderer::Submit(const VertexBuffer& buffer)
{
    glUseProgram(m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glDrawArrays(GL_TRIANGLES, 0, buffer.GetSize());
}

void Renderer::Submit(const IndexBuffer& buffer)
{
    // glUseProgram(m_RendererID);
    // glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // glDrawArrays(GL_TRIANGLES, 0, buffer.GetSize());
}

void Renderer::Render() { glfwSwapBuffers(m_Window); }

}