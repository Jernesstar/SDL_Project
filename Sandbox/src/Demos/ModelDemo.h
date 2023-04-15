#include <Saddle/Core/Application.h>

#include <OpenGL/Shader.h>

#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Mesh.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>
#include <Saddle/Renderer/Renderer.h>

using namespace Saddle;

class ModelDemo : public Application {
public:
    ModelDemo();

    void OnUpdate(TimeStep ts) override;

private:
    Shader m_Shader{ "Sandbox/assets/shaders/3DModel.glsl.vert", "Sandbox/assets/shaders/3DModel.glsl.frag" };
    
    StereographicCamera m_Camera;
    CameraController m_Controller{ m_Camera };

    Mesh m_Mesh;
};

ModelDemo::ModelDemo()
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

void ModelDemo::OnUpdate(TimeStep ts)
{
    Renderer::Clear();

    m_Controller.OnUpdate(ts);
    m_Shader.SetUniformMatrix4("u_ViewProj", m_Camera.GetViewProjection());

    Renderer::RenderMesh(&m_Mesh);
}