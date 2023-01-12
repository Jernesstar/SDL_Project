#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear(const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 0.0f });

    static void Submit(const VertexArray* vertex_array, uint32_t index_count = 0);

private:
    Renderer() = delete;
    ~Renderer() = delete;
};

}