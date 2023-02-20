#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <glm/vec3.hpp>

#include <Saddle/Core/Application.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();

    void OnUpdate(TimeStep ts) override;
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    struct Character {
        uint32_t   TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;      // Size of glyph1
        glm::ivec2 Bearing;   // Offset from baseline to left/top of glyph
        uint32_t   Advance;   // Offset to advance to next glyph
    };

    std::unordered_map<char, Character> Characters;

    Shader m_Shader{ "Sandbox/assets/shaders/Text.glsl.vert", "Sandbox/assets/shaders/Text.glsl.frag" };

    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
    VertexArray* m_VertexArray;
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
    m_Shader.SetUniformMatrix4("projection", projection);

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

    BufferLayout layout =
    {
        {"PosTextCoord", BufferDataType::Vec4 }
    };

    uint32_t indices[6] =
    {
        0, 2, 3,
        3, 1, 0
    };

    m_IndexBuffer = new IndexBuffer(indices);
    m_VertexBuffer = new VertexBuffer(4, layout);
    m_VertexArray = new VertexArray(m_VertexBuffer, m_IndexBuffer);
}

void FontDemo::OnUpdate(TimeStep ts)
{
    RenderText("This is sample text", 300.0f, 300.0f, 1.0f, glm::vec3(0.6f, 0.7f, 0.8f));
}

void FontDemo::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    m_Shader.Bind();
    m_Shader.SetUniformVec3("textColor", color);
    m_VertexArray->Bind();
    m_VertexBuffer->Bind();

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[4][4] =
        {
            { xpos, ypos, 0.0f, 1.0f },
            { xpos + w, ypos, 1.0f, 1.0f },
            { xpos, ypos + h,     0.0f, 0.0f },
            { xpos + w, ypos + h,     1.0f, 0.0f },
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        m_VertexBuffer->SetData(vertices, sizeof(vertices));
        // render quad
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->Count, GL_UNSIGNED_INT, nullptr);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
}