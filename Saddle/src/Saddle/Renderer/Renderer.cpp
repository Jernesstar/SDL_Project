#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Log.h"

#include "Renderer2D.h"

namespace Saddle {

void Renderer::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    Renderer2D::Init();
}

void Renderer::Clear(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Submit(const VertexArray& vertex_array)
{
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, vertex_array.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
}

}