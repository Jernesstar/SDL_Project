#pragma once

#include <glad/glad.h>

#include "OpenGL/Shader.h"
#include "OpenGL/VertexBuffer.h"

namespace Saddle {

class Renderer {
public:
    static void Init();
    static void Clear();

    static void Submit(Shader vertex_shader, Shader fragment_shader);
    // static void DrawTexture(const Texture2D& texture, const Transform& transform);
    static void Render(const VertexBuffer& buffer);
    // static void SetPixel(SDL_Surface* surface, int x, int y, RGBColor color);

private:
    inline static GLint m_RendererID;

    Renderer() = delete;
    ~Renderer() = delete;
};

}