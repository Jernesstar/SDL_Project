#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

namespace Saddle {

struct VertexBuffer {
    VertexBuffer()
    {
        glGenBuffers(1, &m_VertexBufferID);
    }

    operator int() const { return m_VertexBufferID; }

private:
    GLuint m_VertexBufferID;
};

}