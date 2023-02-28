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
    float ratio{ this->Window.GetAspectRatio() };

    OrthographicCamera camera{ -ratio, ratio, -1.0f, 1.0f };
};