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
    static void Clear(glm::vec4 color = { 0.0f, 0.0f, 0.0f, 0.0f });

    static void BindShaders(const Shader& shader);
    static void BindShaders(const Shader& vertex_shader, const Shader& fragment_shader);
    static void UnbindShader();

    static void Submit(const VertexBuffer& buffer);
    static void Submit(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer);
    static void Submit(const VertexArray& vertex_array);

    static void Render();

    static unsigned int GetRendererID() { return m_RendererID; }

private:
    inline static unsigned int m_RendererID;
    inline static GLFWwindow* m_Window;

    Renderer() = delete;
    ~Renderer() = delete;
};

}