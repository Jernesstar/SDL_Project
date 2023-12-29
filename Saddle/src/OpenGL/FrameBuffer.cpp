#include "FrameBuffer.h"

namespace Saddle
{

FrameBuffer::FrameBuffer(AttachmentType type, int w, int h)
{
        glGenFramebuffers(1, &m_BufferID);

        switch(type)
        {
            case AttachmentType::Texture:
                uint32_t texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);  
                break;

            case AttachmentType::RenderBuffer:
                break;
        }
}

}