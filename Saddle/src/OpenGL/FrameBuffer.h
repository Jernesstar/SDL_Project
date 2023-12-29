#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

#include "Saddle/Core/Log.h"

namespace Saddle {

class FrameBuffer {
public:
    FrameBuffer(const void* data = nullptr)
    {
        glGenFramebuffers(1, &m_BufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
    }

    ~FrameBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void SetData(const void* data, uint32_t size = 0, uint32_t offset = 0)
    {
    }

private:
    uint32_t m_BufferID;
};

}