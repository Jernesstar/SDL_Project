#include "VertexBuffer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

VertexBuffer::VertexBuffer(unsigned int count, const Vertex* vertices)
    : m_Count(count), m_Size(count * sizeof(Vertex))
{
    glCreateBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_Size, vertices, GL_DYNAMIC_DRAW);

    // Enabling a vertex attribute
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Setting the data for the attribute: 
    // 1. the attribute index, 2. the number of elements that make up the attribute, 3. The type of the elements
    // 4. whether of not to normalize to values, 5. the size in bytes of the whole vertex
    // 6. a pointer to the start of the attribute in each vertex
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(const Vertex* vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, vertices);
}

}