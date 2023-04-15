#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Log.h"

#include "Renderer2D.h"

namespace Saddle {

void Renderer::Init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

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
    glDrawElements(GL_TRIANGLES, indices != 0 ? indices : vertex_array->GetIndexBuffer()->Count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::RenderMesh(Mesh* mesh)
{
    mesh->m_VertexArray->Bind();

    for(uint32_t i = 0; i < mesh->GetSubMeshCount(); i++)
    {
        const Mesh::SubMesh& sub_mesh = mesh->m_SubMeshes[i];
        uint32_t material_index = sub_mesh.MaterialIndex;

        if(mesh->m_Materials[material_index].Diffuse)
            mesh->m_Materials[material_index].Diffuse->Bind(0);

        glDrawElementsBaseVertex(GL_TRIANGLES, sub_mesh.IndexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * sub_mesh.BaseIndex), sub_mesh.BaseVertex);
    }
}


}