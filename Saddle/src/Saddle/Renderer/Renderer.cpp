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

void Renderer::BindShader(const Shader& shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, shader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
    glUseProgram(m_RendererID);
}

void Renderer::BindShader(const Shader& vertex_shader, const Shader& fragment_shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertex_shader);
    glAttachShader(m_RendererID, fragment_shader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
    glUseProgram(m_RendererID);
}

void Renderer::UnbindShader() { glUseProgram(0); }

void Renderer::Submit(const VertexBuffer& buffer)
{
    buffer.Bind();
    glDrawArrays(GL_TRIANGLES, 0, buffer.GetCount());
    buffer.Unbind();
}

void Renderer::Submit(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer)
{
    vertex_buffer.Bind();
    index_buffer.Bind();
    glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    index_buffer.Unbind();
    vertex_buffer.Unbind();
}

void Renderer::Render() { glfwSwapBuffers(m_Window); }

}