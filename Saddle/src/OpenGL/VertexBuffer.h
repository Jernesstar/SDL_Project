#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

namespace Saddle {

class VertexBuffer {
public:
    const BufferLayout Layout;
    const uint32_t Count;

public:
    template<typename T, std::size_t TCount>
    VertexBuffer(const T (&vertices)[TCount], const BufferLayout& layout)
        : Count(TCount), Layout(layout)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, Count * Layout.Stride, vertices, GL_DYNAMIC_DRAW);
    }

    VertexBuffer(std::size_t count, const BufferLayout& layout)
        : Layout(layout), Count(count)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, Count * Layout.Stride, nullptr, GL_DYNAMIC_DRAW);
    }

    ~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    template<typename T, std::size_t TCount>
    void SetData(const T (&vertices)[TCount])
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, TCount * Layout.Stride, vertices);
    }

    void SetData(const void* data, std::size_t count)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * Layout.Stride, data);
    }

private:
    uint32_t m_VertexBufferID;
};

}