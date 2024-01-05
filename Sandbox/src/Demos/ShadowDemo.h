#include <OpenGL/FrameBuffer.h>

#include <Saddle/Core/Application.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>
#include <Saddle/Text/Font.h>
#include <Saddle/Text/Text.h>

using namespace Saddle;

class ShadowDemo : public Application {
public:
    ShadowDemo();

    void OnUpdate(TimeStep ts) override;

private:
    FrameBuffer* depth_map;

    StereographicCamera camera{ 90.0f, 0.1f, 100.0f, 1600, 900 };
    CameraController controller{ camera };
};

ShadowDemo::ShadowDemo()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event)
    {
        if(event.Key == Key::Escape)
            Application::Close();
    });

    depth_map = new FrameBuffer({
        800, 1960, AttachmentType::None, AttachmentType::Texture, AttachmentType::None
    });

    camera.SetPosition({ 0.0f, 0.0f, 1.0f });
    controller.TranslationSpeed = 0.5f;
}

void ShadowDemo::OnUpdate(TimeStep ts)
{
    controller.OnUpdate(ts);

    Renderer::Clear({ 0.0f, 0.0f, 0.0f, 0.0f });
}