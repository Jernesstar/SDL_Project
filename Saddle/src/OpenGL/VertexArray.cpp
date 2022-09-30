#include "VertexArray.h"

#include <glad/glad.h>

namespace Saddle {

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_VertexArrayID);
}

VertexArray::VertexArray(VertexBuffer& vertex_buffer)
{
    glCreateVertexArrays(1, &m_VertexArrayID);
    SetVertexBuffer(vertex_buffer);
}

VertexArray::VertexArray(IndexBuffer& index_buffer)
{
    glCreateVertexArrays(1, &m_VertexArrayID);
    SetIndexBuffer(index_buffer);
}

VertexArray::VertexArray(VertexBuffer& vertex_buffer, IndexBuffer& index_buffer)
{
    glCreateVertexArrays(1, &m_VertexArrayID);
    SetVertexBuffer(vertex_buffer);
    SetIndexBuffer(index_buffer);
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_VertexArrayID);
    delete m_VertexBuffer; m_VertexBuffer = nullptr;
    delete m_IndexBuffer; m_IndexBuffer = nullptr;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_VertexArrayID);
    if(m_IndexBuffer) m_IndexBuffer->Bind();
}
void VertexArray::Unbind() const
{
    glBindVertexArray(0);
    if(m_IndexBuffer) m_IndexBuffer->Unbind();
}

void VertexArray::SetVertexBuffer(VertexBuffer& vertex_buffer)
{
    glBindVertexArray(m_VertexArrayID);
    vertex_buffer.Bind();

    // Enabling a vertex attribute
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Setting the data for the attribute: 
    // 1. the attribute index, 2. the number of elements that make up the attribute, 3. The type of the elements
    // 4. whether of not to normalize to values, 5. the size in bytes of the whole vertex
    // 6. a pointer to the start of the attribute in each vertex
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    m_VertexBuffer = &vertex_buffer;
    vertex_buffer.Unbind();
}

void VertexArray::SetIndexBuffer(IndexBuffer& index_buffer)
{
    glBindVertexArray(m_VertexArrayID);
    index_buffer.Bind();
    m_IndexBuffer = &index_buffer;
    index_buffer.Unbind();
}

}