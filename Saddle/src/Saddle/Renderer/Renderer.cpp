#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Log.h"

namespace Saddle {

void Renderer::Init()
{
    m_Window = Application::Get().GetWindow().GetNativeWindow();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Submit(const VertexArray& vertex_array, const Shader& shader)
{
    shader.Bind();
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Render() { glfwSwapBuffers(m_Window); }

}