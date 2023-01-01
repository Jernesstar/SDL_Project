#pragma once

#include <glm/mat4x4.hpp>

#include "Saddle/ECS/Entity.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"

namespace Saddle {

class Renderer2D {
public:
    static void Init();
    static void DrawTexture(const Texture2D& texture, const glm::mat4& transform);
    static void DrawEntity(const Entity& entity);

private:
    inline static Shader* s_Shader;
    inline static VertexArray* s_VertexArray;
};

}