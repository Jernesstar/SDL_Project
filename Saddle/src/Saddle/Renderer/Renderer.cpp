#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { m_Window = Application::Get().GetWindow().GetNativeWindow(); }

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BindShaders(const Shader& shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, shader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
    glUseProgram(m_RendererID);
}

void Renderer::BindShaders(const Shader& vertex_shader, const Shader& fragment_shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertex_shader);
    glAttachShader(m_RendererID, fragment_shader);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);
    glUseProgram(m_RendererID);
}

void Renderer::UnbindShader() { glUseProgram(0); }

void Renderer::Submit(const VertexArray& vertex_array)
{
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    vertex_array.Unbind();
}

void Renderer::Render() { glfwSwapBuffers(m_Window); }

}