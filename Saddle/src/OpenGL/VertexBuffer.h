#pragma once

#include <glad/glad.h>

namespace Saddle {

struct VertexBuffer {
    VertexBuffer();

    operator int() const { return m_VertexBufferID; }

private:
    GLuint m_VertexBufferID;
};

}