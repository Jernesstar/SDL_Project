#include <Saddle/Core/Application.h>

#include <OpenGL/Shader.h>

#include <Saddle/Renderer/Mesh.h>

using namespace Saddle;

class MineCraft : public Application {
public:
    MineCraft();

    void OnUpdate(TimeStep ts) override;

private:
    Shader m_Shader{ "Sandbox/assets/shaders/3D.glsl.vert", "Sandbox/assets/shaders/3D.glsl.frag" };

    Mesh m_Mesh;
};