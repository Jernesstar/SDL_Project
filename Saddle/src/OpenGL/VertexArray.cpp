#include "VertexArray.h"

#include <iostream>
#include <cstring>

#include <glad/glad.h>

namespace Saddle {

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_VertexArrayID);
}

VertexArray::VertexArray(VertexBuffer* vertex_buffer, IndexBuffer* index_buffer)
{
    glCreateVertexArrays(1, &m_VertexArrayID);
    AddVertexBuffer(vertex_buffer);
    SetIndexBuffer(index_buffer);
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_VertexArrayID); }

void VertexArray::Bind() const
{
    glBindVertexArray(m_VertexArrayID);
    m_IndexBuffer->Bind();
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
    m_IndexBuffer->Unbind();
}

void VertexArray::AddVertexBuffer(VertexBuffer* vertex_buffer)
{
    glBindVertexArray(m_VertexArrayID);
    vertex_buffer->Bind();

    uint64_t offset = 0;
    uint32_t buffer_index = 0;
    const auto& layout = vertex_buffer->Layout;

    for(auto& element : layout)
    {
        switch(element.Type)
        {
            case BufferDataType::Float:
            case BufferDataType::Vec2:
            case BufferDataType::Vec3:
            case BufferDataType::Vec4:
            {
                glEnableVertexAttribArray(buffer_index);
                glVertexAttribPointer(
                    buffer_index, element.ComponentCount, GL_FLOAT,
                    element.Normalized ? GL_FALSE : GL_TRUE,
                    layout.Stride, (void*)offset
                );

                buffer_index++;
                break;
            }

            case BufferDataType::Int:
            {
                glEnableVertexAttribArray(buffer_index);
                glVertexAttribIPointer(
                    buffer_index, element.ComponentCount, GL_INT,
                    layout.Stride, (void*)offset
                );

                buffer_index++;
                break;
            }

            case BufferDataType::Mat2:
            case BufferDataType::Mat3:
            case BufferDataType::Mat4:
            {
                for(uint32_t i = 0; i < element.ComponentCount; i++)
                {
                    glEnableVertexAttribArray(buffer_index);
                    glVertexAttribPointer(
                        buffer_index, element.ComponentCount, GL_FLOAT,
                        element.Normalized ? GL_FALSE : GL_TRUE, layout.Stride, 
                        (void*)(offset + (sizeof(float) * element.ComponentCount * i))
                    );
                    glVertexAttribDivisor(buffer_index, 1);
                    buffer_index++;
                }
                break;
            }
        }
        offset += element.Size;
    }

    m_VertexBuffers.push_back(vertex_buffer);
}

void VertexArray::SetIndexBuffer(IndexBuffer* index_buffer)
{
    glBindVertexArray(m_VertexArrayID);
    m_IndexBuffer = index_buffer;
}

}