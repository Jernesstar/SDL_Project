#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Log.h"

#include "Renderer2D.h"

namespace Saddle {

VertexBuffer* Renderer::s_CubemapBuffer;
VertexArray* Renderer::s_CubemapArray;

void Renderer::Init()
{
    glEnable(GL_DEPTH_TEST); // Depth testing
    glEnable(GL_MULTISAMPLE); // Smooth edges
    glEnable(GL_FRAMEBUFFER_SRGB); // Gamma correction
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // ???

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    float vertices[6 * 6 * 3] =
    {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    s_CubemapBuffer = new VertexBuffer(vertices, BufferLayout{ { "Position", BufferDataType::Vec3 } });
    s_CubemapArray = new VertexArray(s_CubemapBuffer);

    Renderer2D::Init();
}

void Renderer::Clear(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawIndexed(const VertexArray* vertex_array, uint32_t indices)
{
    vertex_array->Bind();
    glDrawElements(GL_TRIANGLES, indices != 0 ? indices : vertex_array->GetIndexBuffer()->Count,
        GL_UNSIGNED_INT, nullptr);
}

void Renderer::RenderMesh(Mesh* mesh)
{
    mesh->m_VertexArray->Bind();

    for(uint32_t i = 0; i < mesh->GetSubMeshCount(); i++)
    {
        const Mesh::SubMesh& sub_mesh = mesh->m_SubMeshes[i];
        uint32_t material_index = sub_mesh.MaterialIndex;

        mesh->m_Materials[material_index].Bind();

        glDrawElementsBaseVertex(GL_TRIANGLES, sub_mesh.IndexCount, GL_UNSIGNED_INT,
            (void*)(sizeof(uint32_t) * sub_mesh.BaseIndex), sub_mesh.BaseVertex);
    }
}

void Renderer::RenderCubemap(Cubemap* cubemap)
{
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    cubemap->Bind();
    s_CubemapArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthFunc(GL_LESS);
}

}