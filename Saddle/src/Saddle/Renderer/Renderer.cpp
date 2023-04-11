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

    // glEnable(GL_DEPTH_TEST);

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
        if(mesh->m_Textures[i])
            mesh->m_Textures[i]->Bind(0);
        
        glDrawElementsBaseVertex(GL_TRIANGLES,
                                mesh->m_SubMeshes[i].IndexCount,
                                GL_UNSIGNED_INT,
                                (void*)(sizeof(uint32_t) * mesh->m_SubMeshes[i].BaseIndex),
                                mesh->m_SubMeshes[i].BaseVertex);
    }
}


}