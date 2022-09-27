#pragma once

#include "Vertex.h"

namespace Saddle {

class VertexBuffer {
public:
    VertexBuffer(unsigned int size, const Vertex* vertices = nullptr);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(const Vertex* vertices);

    const unsigned int GetCount() const { return m_Count; }
    const unsigned int GetSize() const { return m_Size; }
    
    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
    unsigned int m_Count;
    unsigned int m_Size;
};

}