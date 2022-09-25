#include "VertexBuffer.h"

#include <glad/glad.h>

namespace Saddle {

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_VertexBufferID);
    
}

}