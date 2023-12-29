#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

#include "Saddle/Core/Application.h"

namespace Saddle {

enum class AttachmentType { Texture, RenderBuffer };

class FrameBuffer {
public:
    FrameBuffer(AttachmentType type, int width, int height);
    ~FrameBuffer() { glDeleteBuffers(1, &m_BufferID); }

    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID); }
    void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

private:
    uint32_t m_BufferID;
};

}