#pragma once

namespace Saddle {

struct IndexBuffer {
    template<std::size_t Count>
    IndexBuffer(const uint32_t (&indices)[Count])
        : m_Count(Count)
    {
        glCreateBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBuffer(const uint32_t* indices, std::size_t count)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~IndexBuffer() { glDeleteBuffers(1, &m_IndexBufferID); }

    void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID); }
    void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    const uint32_t GetCount() const { return m_Count; }

private:
    uint32_t m_IndexBufferID;
    uint32_t m_Count;
};

}