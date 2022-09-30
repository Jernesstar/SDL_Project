#pragma once

#include <glad/glad.h>

#include "Vertex.h"

namespace Saddle {

class VertexBuffer {
public:
    template<std::size_t Count>
    VertexBuffer(const Vertex (&vertices)[Count])
        : m_Count(Count)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(Vertex), vertices, GL_DYNAMIC_DRAW);
    }
    ~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void SetData(const Vertex* vertices)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Count * sizeof(Vertex), vertices);
    }

    const unsigned int GetCount() const { return m_Count; }
    
    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
    unsigned int m_Count;
};

}