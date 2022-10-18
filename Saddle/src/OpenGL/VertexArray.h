#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"

namespace Saddle {

class VertexArray {
public:
    template<typename TVertex, std::size_t TVertexCount, std::size_t TIndexCount>
    VertexArray(const TVertex (&vertices)[TVertexCount], const BufferLayout& layout,
        const uint32_t (&indices)[TIndexCount])
        : m_VertexBuffer(vertices, layout), m_IndexBuffer(indices)
    {
        glCreateVertexArrays(1, &m_VertexArrayID);
        SetVertexBuffer(m_VertexBuffer);
        SetIndexBuffer(m_IndexBuffer);
    }

    VertexArray(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer);
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(const VertexBuffer& vertex_buffer);
    void SetIndexBuffer(const IndexBuffer& index_buffer);

    const VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }
    const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_VertexArrayID;

    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;
};

}