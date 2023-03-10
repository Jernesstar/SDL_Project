#pragma once

#include <glm/mat4x4.hpp>

#include "OrthographicCamera.h"

#include "Saddle/ECS/Entity.h"
#include "Saddle/ECS/Entity.h"
#include "Saddle/Text/Text.h"

#include "OpenGL/Texture2D.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"

namespace Saddle {

class Renderer2D {
public:
    static void Init();
    static void BeginScene(const OrthographicCamera& camera);

    static void DrawEntity(Entity& entity, float scale = 1.0f);
    static void DrawEntity(Entity& entity, const glm::vec2& size);

    static void DrawText(const Text& text, const glm::mat4& transform);
    static void DrawText(const Text& text, const glm::vec2& position, float scale = 1.0f);

    static void DrawQuad(const glm::vec4& color, const glm::mat4& transform);
    static void DrawQuad(const glm::vec4& color, const glm::vec2& position, const glm::vec2& size);

    static void DrawQuad(Texture2D* texture, const glm::mat4& transform);
    static void DrawQuad(Texture2D* texture, const glm::vec2& position, float scale = 1.0f);
    static void DrawQuad(Texture2D* texture, const glm::vec2& position, const glm::vec2& size);

    static void DrawQuad(const Text::CharacterQuad& ch, const glm::vec4& color, const glm::mat4& transform);

    static void EndScene();

private:
    inline static glm::mat4 s_ViewProjMatrix{ 1.0f };

    static void StartBatch();
    static void Flush();
    static void NextBatch();
};

}