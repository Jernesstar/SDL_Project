#include "VertexArray.h"

#include <iostream>

#include <glad/glad.h>

namespace Saddle {

static GLenum BufferDataTypeToOpenGLType(BufferDataType type)
{
    switch (type)
    {
        case BufferDataType::Float: return GL_FLOAT;
        case BufferDataType::Int:   return GL_INT;
        case BufferDataType::Vec2:  return GL_FLOAT;
        case BufferDataType::Vec3:  return GL_FLOAT;
        case BufferDataType::Vec4:  return GL_FLOAT;
        case BufferDataType::Mat2:  return GL_FLOAT;
        case BufferDataType::Mat3:  return GL_FLOAT;
        case BufferDataType::Mat4:  return GL_FLOAT;
    }
    return 0;
}

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
    delete m_VertexBuffer;
    delete m_IndexBuffer;
    m_VertexBuffer = nullptr;
    m_IndexBuffer = nullptr;
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

    // Enabling a vertex attribute: glEnableVertexAttribArray

    // Setting the data for the attribute: glVertexAttribPointer
    // 1. the attribute index, 2. the number of elements that make up the attribute, 3. The type of the elements
    // 4. whether of not to normalize to values, 5. the size in bytes of the whole vertex
    // 6. a pointer to the start of the attribute in each vertex

    int offset = 0;
    auto& layout = vertex_buffer.Layout;

    for(auto& element : layout)
    {
        switch(element.Type)
        {
            case BufferDataType::Float:
            case BufferDataType::Vec2:
            case BufferDataType::Vec3:
            case BufferDataType::Vec4:
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(
                    m_VertexBufferIndex, element.ComponentCount, 
                    BufferDataTypeToOpenGLType(element.Type),
                    element.Normalized ? GL_FALSE : GL_TRUE,
                    layout.Stride, (void*)offset
                );

                offset += element.Size;
                m_VertexBufferIndex++;
                break;
            }

            case BufferDataType::Int:
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribIPointer(
                    m_VertexBufferIndex, element.ComponentCount,
                    BufferDataTypeToOpenGLType(element.Type),
                    layout.Stride, (void*)offset
                );

                offset += element.Size;
                m_VertexBufferIndex++;
                break;
            }

            case BufferDataType::Mat2:
            case BufferDataType::Mat3:
            case BufferDataType::Mat4:
            {
                for(int i = 0; i < element.ComponentCount; i++)
                {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(
                        m_VertexBufferIndex, element.ComponentCount, 
                        BufferDataTypeToOpenGLType(element.Type),
                        element.Normalized ? GL_FALSE : GL_TRUE,
                        layout.Stride, (void*)(offset + (sizeof(float) * element.ComponentCount * i))
                    );
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }

                offset += element.Size;
                break;
            }
        }
    }

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