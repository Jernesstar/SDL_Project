#include "Renderer.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"

namespace Saddle {

void Renderer::Init() { m_RendererID = glCreateProgram(); }

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Submit(Shader shader)
{
    glAttachShader(m_RendererID, shader);
}

void Renderer::Render()
{
    glLinkProgram(m_RendererID);
    glUseProgram(m_RendererID);
}

}