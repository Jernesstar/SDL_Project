#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Cubemap.h"

#include "Mesh.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear(const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 0.0f });

    static void DrawIndexed(const VertexArray* vertex_array, uint32_t indices = 0);
    static void RenderMesh(Mesh* mesh);
    static void RenderCubemap(Cubemap* cubemap);

private:
    static VertexArray* s_CubemapArray;

private:
    Renderer() = delete;
    ~Renderer() = delete;
};

}