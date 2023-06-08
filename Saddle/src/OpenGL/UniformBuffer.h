#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

#include "Saddle/Core/Log.h"

namespace Saddle {

class UniformBuffer {
public:
    const uint32_t Binding;
    const std::string Name;

public:
    UniformBuffer(const std::string& name, uint32_t binding, std::size_t size, const void* data = nullptr, bool dynamic = true)
        : Name(name), Binding(binding)
    {
        glCreateBuffers(1, &m_BufferID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
        glBufferData(GL_UNIFORM_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        // glNamedBufferData(m_BufferID, size, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_BufferID);
    }

    ~UniformBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void SetData(const void* data, uint32_t size, uint32_t offset = 0)
    {
        // glNamedBufferSubData(m_BufferID, offset, size, data);
        glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
        glBufferSubData(GL_UNIFORM_BUFFER, size, offset, data);
    }

private:
    uint32_t m_BufferID;
};

}