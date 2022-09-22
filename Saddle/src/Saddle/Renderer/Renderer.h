#pragma once

#include <glad/glad.h>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexBuffer.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear();

    static void Submit(const Shader& vertex_shader, const Shader& fragment_shader);
    // static void DrawTexture(const Texture2D& texture, const Transform& transform);
    static void Render(const VertexBuffer& buffer);
    // static void SetPixel(SDL_Surface* surface, int x, int y, RGBColor color);

    static GLint GetRendererID() { return m_RendererID; }

private:
    inline static GLint m_RendererID;

    Renderer() = delete;
    ~Renderer() = delete;
};

}