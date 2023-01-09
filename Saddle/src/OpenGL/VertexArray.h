#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"

namespace Saddle {

class VertexArray {
public:
    VertexArray(VertexBuffer* vertex_buffer, IndexBuffer* index_buffer);
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(VertexBuffer* vertex_buffer);
    void SetIndexBuffer(IndexBuffer* index_buffer);

    VertexBuffer* GetVertexBuffer() const { return m_VertexBuffer; }
    IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_VertexArrayID;

    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
};

}