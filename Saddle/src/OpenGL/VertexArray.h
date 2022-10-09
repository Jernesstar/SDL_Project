#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Saddle {

class VertexArray {
public:
    VertexArray();
    VertexArray(const VertexBuffer& vertex_buffer);
    VertexArray(const IndexBuffer& index_buffer);
    VertexArray(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer);
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(const VertexBuffer& vertex_buffer);
    void SetIndexBuffer(const IndexBuffer& index_buffer);

    const VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }
    const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; }

private:
    unsigned int m_VertexArrayID;
    int m_VertexBufferIndex = 0;

    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;
};

}