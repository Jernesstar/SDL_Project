#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <Saddle/Core/Application.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();

    void OnUpdate(TimeStep timeStep) override { }

private:
    struct Character {
        uint32_t Texture;  // ID handle of the glyph texture
        glm::ivec2 Size;    // Offset from baseline to left/top of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        uint32_t Advance;    // Offset to advance to next glyph
    };

    std::unordered_map<char, Character> Characters;
};

FontDemo::FontDemo()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        SADDLE_CORE_LOG_ERROR("FREETYPE: Could not init FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, "Sandbox/assets/fonts/pixel_font.ttf", 0, &face))
    {
        SADDLE_CORE_LOG_ERROR("FREETYPE: Failed to load font");  
    }

    FT_Set_Pixel_Sizes(face, 0, 48); // Dynamic width based on the height

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            SADDLE_CORE_LOG_ERROR("FREETYTPE: Failed to load glyph");
        }

        uint32_t w = face->glyph->bitmap.width, h = face->glyph->bitmap.rows;

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture, 
            glm::ivec2(w, h),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (uint32_t)face->glyph->advance.x
        };

        Characters.insert({ c, character });

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
}