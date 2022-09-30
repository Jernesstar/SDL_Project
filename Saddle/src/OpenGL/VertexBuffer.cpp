#include "VertexBuffer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

VertexBuffer::VertexBuffer(unsigned int count, const Vertex* vertices)
    : m_Count(count)
{
    glCreateBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(const Vertex* vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Count * sizeof(Vertex), vertices);
}

}