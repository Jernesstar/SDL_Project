#include "MineCraft.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Events/EventSystem.h>

MineCraft::MineCraft()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event)
    {
        if(event.Key == Key::Escape)
            Application::Close();
    });
    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [this](const WindowResizedEvent& event)
    {
        this->m_Camera.Resize(event.Width, event.Height);
    });

    m_Camera.Resize(1600, 900);
    m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
    m_Camera.SetProjection(90.0f, 0.1f, 100.0f);

    m_Shader.Bind();
    m_Shader.SetUniformMatrix4("u_Model", glm::mat4(1.0f));

    m_Mesh.LoadMesh("Sandbox/assets/models/backpack/backpack.obj");
}

void MineCraft::OnUpdate(TimeStep ts)
{
    Renderer::Clear();

    m_Controller.OnUpdate(ts);
    m_Shader.SetUniformMatrix4("u_ViewProj", m_Camera.GetViewProjection());

    Renderer::RenderMesh(&m_Mesh);
}