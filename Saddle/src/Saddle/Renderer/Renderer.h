#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"

#include "Mesh.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear(const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 0.0f });

    static void DrawIndexed(const VertexArray* vertex_array, uint32_t index_count = 0);
    static void RenderMesh(Mesh* mesh);

private:
    Renderer() = delete;
    ~Renderer() = delete;
};

}