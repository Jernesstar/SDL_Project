#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <glm/vec3.hpp>

#include <Saddle/Core/Application.h>
#include <OpenGL/Shader.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();

    void OnUpdate(TimeStep ts) override;
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    struct Character {
        uint32_t   TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;      // Offset from baseline to left/top of glyph
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        uint32_t   Advance;   // Offset to advance to next glyph
    };

    std::unordered_map<char, Character> Characters;
    uint32_t VAO, VBO;

    Shader m_Shader{ "Sandbox/assets/shaders/Text.glsl.vert", "Sandbox/assets/shaders/Text.glsl.frag" };
    
    glm::vec2 vec{ Window.GetFrameBufferSize() };
    float ratio{ vec.x / vec.y };
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

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, -1.0f);

    m_Shader.Bind();
    m_Shader.SetUniformMatrix4("u_ViewProjMatrix", projection);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
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

        Character character =
        {
            texture,
            glm::ivec2(w, h),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (uint32_t)face->glyph->advance.x
        };

        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
}

void FontDemo::OnUpdate(TimeStep ts)
{
    RenderText("This is sample text", 300.0f, 300.0f, 4.0f, glm::vec3(0.6f, 0.7f, 0.8f));
}

void FontDemo::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    m_Shader.Bind();
    m_Shader.SetUniformVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] =
        {
            { xpos + w, ypos,     1.0f, 0.0f },
            { xpos,     ypos,     0.0f, 0.0f },
            { xpos,     ypos + h, 0.0f, 1.0f },

            { xpos,     ypos + h, 0.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 1.0f },
            { xpos + w, ypos,     0.0f, 0.0f },
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
}