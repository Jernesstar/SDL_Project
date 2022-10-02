#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

namespace Saddle {

class VertexBuffer {
public:
    const BufferLayout Layout;
    const unsigned int Count;

public:
    template<typename T, std::size_t TCount>
    VertexBuffer(const T (&vertices)[TCount], const BufferLayout& layout = BufferLayout())
        : Count(TCount), Layout(layout)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, Count * layout.Stride, vertices, GL_DYNAMIC_DRAW);
    }

    ~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void SetData(const void* vertices)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(float), vertices);
    }

    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
};

}