#pragma once

#include <Saddle/Core/Application.h>
#include <Saddle/ECS/Entity.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/OrthographicCameraController.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>

using namespace Saddle;

class Game : public Application {
public:
    Game();
    ~Game() = default;

    void OnUpdate(TimeStep ts) override;

private:
    Scene m_Scene;
    Entity Kick_Drum{ m_Scene };
    Entity Snare_Drum{ m_Scene };


    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
    OrthographicCameraController controller{ camera };
};