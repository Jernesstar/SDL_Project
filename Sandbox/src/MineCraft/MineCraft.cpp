#include "MineCraft.h"

#include <Saddle/Renderer/Renderer.h>

MineCraft::MineCraft()
{
    m_Shader.Bind();

    m_Mesh.LoadMesh("Sandbox/assets/models/backpack/backpack.obj");
}

void MineCraft::OnUpdate(TimeStep ts)
{
    Renderer::RenderMesh(&m_Mesh);
}