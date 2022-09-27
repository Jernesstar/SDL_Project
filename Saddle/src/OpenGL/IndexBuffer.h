#pragma once

namespace Saddle {

struct IndexBuffer {
    IndexBuffer(unsigned int size, unsigned int* indices = nullptr);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    const unsigned int GetCount() const { return m_Count; }

    operator int() const { return m_IndexBufferID; }

private:
    unsigned int m_IndexBufferID;
    unsigned int m_Count;
};

}