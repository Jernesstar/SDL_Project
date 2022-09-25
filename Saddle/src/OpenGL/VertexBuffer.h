#pragma once

namespace Saddle {

struct VertexBuffer {
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    operator int() const { return m_VertexBufferID; }

private:
    unsigned int m_VertexBufferID;
};

}