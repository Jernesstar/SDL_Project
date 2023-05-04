#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

#include "Saddle/Core/Log.h"

namespace Saddle {

class UniformBuffer {
public:
    const uint32_t Binding;

public:
    UniformBuffer(uint32_t binding, std::size_t size, bool dynamic = true)
        : Binding(binding)
    {
        glCreateBuffers(1, &m_BufferID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_BufferID);
    }
    ~UniformBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void SetData(const void* data, uint32_t offset, uint32_t size)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data); 
    }

private:
    uint32_t m_BufferID;
};

}