#include "Text.h"

namespace Saddle {

void Text::SetText(const std::string& text, const Font& font, const glm::vec3& color)
{
    float x = 0.0f, y = 0.0f;

    for(std::string::const_iterator c = text.begin(); c != text.end(); c++)
    {
        const Font::Character& ch = font.GetCharacter(*c);

        float xpos = x + ch.Bearing.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y);

        float w = ch.Size.x;
        float h = ch.Size.y;

        glm::vec2 vertices[4] =
        {
            { xpos,     ypos,    }, // 0.0f, 1.0f
            { xpos + w, ypos,    }, // 1.0f, 1.0f
            { xpos,     ypos + h }, // 0.0f, 0.0f
            { xpos + w, ypos + h }, // 1.0f, 0.0f
        };

        x += (ch.Advance >> 6);

        CharacterQuad quad = { ch, vertices };
        m_Quads.push_back(quad);
    }
}

}