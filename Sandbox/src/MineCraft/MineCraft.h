#include <Saddle/Core/Application.h>

#include <OpenGL/Shader.h>

#include <Saddle/Renderer/Mesh.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>

using namespace Saddle;

class MineCraft : public Application {
public:
    MineCraft();

    void OnUpdate(TimeStep ts) override;

private:
    Shader m_Shader{ "Sandbox/assets/shaders/3DModel.glsl.vert", "Sandbox/assets/shaders/3DModel.glsl.frag" };
    
    StereographicCamera m_Camera;
    CameraController m_Controller{ m_Camera };

    Mesh m_Mesh;
};