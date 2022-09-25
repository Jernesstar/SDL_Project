#pragma once

namespace Saddle {

struct VertexBuffer {
    VertexBuffer(unsigned int size);
    VertexBuffer(unsigned int size, void* data);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(unsigned int size, void* data);

    const unsigned int GetSize() const { return m_Size; }
    
    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
    unsigned int m_Size;
};

}