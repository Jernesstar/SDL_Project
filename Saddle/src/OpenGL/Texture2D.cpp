#include "Texture2D.h"

#include <cstring>

#include <stb_image/stb_image.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

Texture2D::Texture2D(const std::string& path)
    : Path(path), InternalFormat(GL_RGBA8), DataFormat(GL_RGBA), m_Slot(0)
{
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pixel_data = stbi_load(path.c_str(), &Width, &Height, &BitsPerPixel, 4);

    SADDLE_CORE_ASSERT(pixel_data);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID); // Creating 2D texture
    glTextureStorage2D(m_TextureID, 1, InternalFormat, Width, Height);

    glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Setting the behavior for miniaturization
    glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Setting the behavior of magnification

    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_TextureID, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, pixel_data);

    stbi_image_free(pixel_data);
}

Texture2D::~Texture2D() { glDeleteTextures(1, &m_TextureID); }

void Texture2D::Bind(uint32_t slot)
{
    m_Slot = slot;
    glBindTextureUnit(slot, m_TextureID);
}

}