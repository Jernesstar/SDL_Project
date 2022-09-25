#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear(float r, float g, float b, float a);

    static void BindShaders(const Shader& vertex_shader, const Shader& fragment_shader);
    static void Submit(const VertexBuffer& buffer);
    static void Submit(const IndexBuffer& buffer);
    static void Render();

    static unsigned int GetRendererID() { return m_RendererID; }

private:
    inline static unsigned int m_RendererID;
    inline static GLFWwindow* m_Window;

    Renderer() = delete;
    ~Renderer() = delete;
};

}