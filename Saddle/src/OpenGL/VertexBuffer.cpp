#include "VertexBuffer.h"

#include <glad/glad.h>

namespace Saddle {

VertexBuffer::VertexBuffer(unsigned int size, const Vertex* data)
    : m_Size(size)
{
    glCreateBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(unsigned int size, const Vertex* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

}