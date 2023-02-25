#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <glm/vec3.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Text/Font.h>
#include <Saddle/Text/Text.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();

    void OnUpdate(TimeStep ts) override;

private:
    Font m_Font{ "Sandbox/assets/fonts/pixel_font.ttf", 0, 48 };
    Text m_Text{ "This is a whooooooole buuuuunch of saaaample text", m_Font, glm::vec3(0.6, 0.7, 0.8) };

    TransformComponent m_Transform =
    {
        glm::vec3{ 600.0f, 400.0f, 0.f }, 
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 1.0f, 1.0f, 1.0f }
    };

    glm::mat4 transform{ m_Transform.GetTransform() };

    OrthographicCamera camera{ 0.0f, 1600.0f, 0.0f, 900.0f };
};

FontDemo::FontDemo() { }

void FontDemo::OnUpdate(TimeStep ts)
{
    Renderer2D::BeginScene(camera);

    Renderer2D::DrawText(m_Text, transform);

    Renderer2D::EndScene();
}