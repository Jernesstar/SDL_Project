#include "MineCraft.h"

#include <Saddle/Renderer/Renderer.h>

MineCraft::MineCraft()
{
    m_Mesh.LoadMesh("Sandbox/assets/models/backpack/backpack.obj");
    m_Shader.Bind();
}


void MineCraft::OnUpdate(TimeStep ts)
{
    Renderer::RenderMesh(&m_Mesh);
}