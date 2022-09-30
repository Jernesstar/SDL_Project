#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Saddle {

class VertexArray {
public:
    VertexArray();
    VertexArray(VertexBuffer& vertex_buffer);
    VertexArray(IndexBuffer& index_buffer);
    VertexArray(VertexBuffer& vertex_buffer, IndexBuffer& index_buffer);
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(VertexBuffer& vertex_buffer);
    void SetIndexBuffer(IndexBuffer& index_buffer);

    const VertexBuffer* GetVertexBuffer() const { return m_VertexBuffer; }
    const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

private:
    unsigned int m_VertexArrayID;

    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
};

}