#include "UniformBuffer.h"

#include <glad/glad.h>

#include "Saddle/Core/Log.h"

namespace Saddle {

UniformBuffer::UniformBuffer(const BufferLayout& layout, uint32_t binding)
    : Layout(layout), Binding(binding)
{
    glCreateBuffers(1, &m_BufferID);
    glNamedBufferData(m_BufferID, layout.Stride, nullptr, layout.Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_BufferID);
}

UniformBuffer::~UniformBuffer() { glDeleteBuffers(1, &m_BufferID); }

void UniformBuffer::SetData(uint32_t offset, uint32_t size, const void* data)
{
    glNamedBufferSubData(m_BufferID, offset, size, data);
}

void UniformBuffer::SetData(const std::string& name, const void* data)
{
    uint32_t offset = 0;
    uint32_t size = 0;
    for(auto& element : Layout)
    {
        if(element.Name != name)
            offset += element.Size;
        else
        {
            size = element.Size;
            break;
        }
    }

    if(size == 0)
    {
        SADDLE_CORE_LOG_WARNING("Buffer element '%s' was not found", name.c_str());
        return;
    }

    glNamedBufferSubData(m_BufferID, offset, size, data);
}


}