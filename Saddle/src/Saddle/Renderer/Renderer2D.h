#pragma once

#include <glm/mat4x4.hpp>

#include "OrthographicCamera.h"

#include "Saddle/ECS/Entity.h"
#include "Saddle/ECS/Entity.h"

#include "OpenGL/Texture2D.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"

namespace Saddle {

class Renderer2D {
public:
    static void Init();
    static void BeginScene(const OrthographicCamera& camera);
    static void DrawTexture(Texture2D& texture, const glm::mat4& transform);
    static void DrawEntity(Entity& entity);

private:
    inline static glm::mat4 s_ViewMatrix{ 1.0f };
    inline static glm::mat4 s_ProjectionMatrix{ 1.0f };

    void StartBatch();
    void Flush();
    void NextBatch();
};

}