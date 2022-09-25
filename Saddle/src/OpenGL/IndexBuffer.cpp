#include "IndexBuffer.h"

#include <glad/glad.h>

namespace Saddle {

IndexBuffer::IndexBuffer(unsigned int count)
    : m_Count(count)
{
    glCreateBuffers(1, &m_IndexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
    glBufferData(GL_ARRAY_BUFFER, count, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::IndexBuffer(unsigned int count, unsigned int* data)
    : m_Count(count)
{
    glCreateBuffers(1, &m_IndexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
    glBufferData(GL_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_IndexBufferID); }

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

}