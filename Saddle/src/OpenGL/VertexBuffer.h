#pragma once

#include "Vertex.h"

namespace Saddle {

class VertexBuffer {
public:
    VertexBuffer(unsigned int size, const Vertex* data = nullptr);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(unsigned int size, const Vertex* data);

    const unsigned int GetSize() const { return m_Size; }
    
    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
    unsigned int m_Size;
};

}