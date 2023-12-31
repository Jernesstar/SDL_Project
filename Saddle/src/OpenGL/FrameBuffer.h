#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

#include "Saddle/Core/Application.h"

namespace Saddle {

class FrameBuffer {
private:
    enum class AttachmentType { Texture, RenderBuffer };

    struct AttachmentSpecification {
        uint32_t Width, Height;
        AttachmentType Color, Depth, Stencil;

        AttachmentSpecification(uint32_t width, uint32_t height,
            AttachmentType color = AttachmentType::Texture,
            AttachmentType depth = AttachmentType::RenderBuffer,
            AttachmentType stencil = AttachmentType::RenderBuffer
        ) : Width(width), Height(height), Color(color), Depth(depth), Stencil(stencil) { }
    };

public:
    FrameBuffer(AttachmentSpecification specs);
    ~FrameBuffer();

    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID); }
    void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

private:
    uint32_t m_BufferID;
    uint32_t m_TextureID;
    uint32_t m_RenderBufferID;
};

}