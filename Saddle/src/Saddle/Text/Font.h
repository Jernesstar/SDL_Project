#pragma once

#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <glm/vec3.hpp>

#include <Saddle/Core/Application.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

namespace Saddle {

class Font {
private:
    struct Character {
        uint32_t   TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;      // Size of glyph
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        uint32_t   Advance;   // Offset to advance to next glyph
    };

public:
    const std::string FontPath;

public:
    Font(const std::string& font_path, uint32_t width, uint32_t height);
    ~Font();

    static void Init() { SADDLE_CORE_ASSERT(!FT_Init_FreeType(&s_FT), "Could not initialize FreeType Library"); }
    static void Close() { FT_Done_FreeType(s_FT); }

    void SetWidth(uint32_t width) { FT_Set_Pixel_Sizes(m_Face, width, 0); UpdateCharacters(); }
    void SetHeight(uint32_t height) { FT_Set_Pixel_Sizes(m_Face, 0, height); UpdateCharacters(); };
    void SetSize(uint32_t width, uint32_t height) { FT_Set_Pixel_Sizes(m_Face, width, height); UpdateCharacters(); }

    glm::vec2 GetSize(const std::string& text) const;

    const Character& GetCharacter(char character) const
    {
        SADDLE_CORE_ASSERT_ARGS(m_Characters.find(character) != m_Characters.end(), "%s is not a valid character!", character);
        return m_Characters.at(character);
    };

private:
    FT_Face m_Face;
    std::unordered_map<char, Character> m_Characters;
    
    void DeleteCharacters();
    void UpdateCharacters();

    inline static FT_Library s_FT;

    friend class Text;
};

};