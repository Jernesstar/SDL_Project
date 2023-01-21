#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Core/Input.h>
#include <Saddle/ECS/Entity.h>
#include <Saddle/ECS/ComponentManager.h>
#include <Saddle/Scene/Scene.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/OrthographicCameraController.h>
#include <Saddle/Renderer/Renderer2D.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

class TextureDemo : public Application {
public:
    TextureDemo();

    void OnUpdate(TimeStep ts);

    Texture2D texture1{ "Sandbox/assets/images/kick_drum.png" };
    Texture2D texture2{ "Sandbox/assets/images/snare_drum.jpg" };

    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };

    TransformComponent transform1 =
    {
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 1.f, 1.f, 1.f },
    };

    TransformComponent transform2 =
    {
        glm::vec3{ -1.0f, 0.0f, 0.0f }, 
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 1.f, 1.f, 1.f },
    };

    glm::mat4 model1{ transform1.GetTransfrom() };
    glm::mat4 model2{ transform2.GetTransfrom() };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
    OrthographicCameraController controller{ camera };
};

TextureDemo::TextureDemo()
{
    this->Window.SetWindowIcon("Sandbox/assets/images/start_bg.png");
}

void TextureDemo::OnUpdate(TimeStep ts)
{
    Renderer::Clear({ 1, 1, 1, 1 });

    Renderer2D::BeginScene(camera);

    Renderer2D::DrawQuad(&texture1, model1);
    Renderer2D::DrawQuad(&texture2, model2);

    Renderer2D::EndScene();
}