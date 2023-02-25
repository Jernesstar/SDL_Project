#include "Font.h"

namespace Saddle {

Font::Font(const std::string& font_path, uint32_t width, uint32_t height)
{
    if(FT_New_Face(Font::m_FT, font_path.c_str(), 0, &m_Face))
    {
        SADDLE_CORE_LOG_ERROR("Failed to load font. Path: %s", font_path.c_str());
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    m_Characters.reserve(128);

    SetSize(width, height);
}

void Font::UpdateCharacters()
{
    for(unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if(FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
        {
            SADDLE_CORE_LOG_ERROR("FREETYTPE: Failed to load glyph");
        }

        uint32_t w = m_Face->glyph->bitmap.width, h = m_Face->glyph->bitmap.rows;

        uint32_t textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, m_Face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character =
        {
            textureID,
            glm::ivec2(w, h),
            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
            (uint32_t)m_Face->glyph->advance.x
        };

        m_Characters[c] = character;
    }
}

};