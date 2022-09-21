#include "Renderer.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { }

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Submit(Shader vertex_shader, Shader fragment_shader)
{
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertex_shader);
    glAttachShader(m_RendererID, fragment_shader);
    glLinkProgram(m_RendererID);
}

void Renderer::Render(VertexBuffer buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glUseProgram(m_RendererID);
    glDrawArrays(GL_TRIANGLES, 0, 0);
}

}