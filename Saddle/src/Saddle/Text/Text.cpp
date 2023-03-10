#include "Text.h"

namespace Saddle {

void Text::SetText(const std::string& text, const Font& font)
{
    m_Quads.reserve(text.size());

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
            { xpos,     ypos,    },
            { xpos + w, ypos,    },
            { xpos,     ypos + h },
            { xpos + w, ypos + h },
        };

        x += (ch.Advance >> 6);

        CharacterQuad quad;
        quad.Character = ch;
        quad.Vertices[0] = vertices[0];
        quad.Vertices[1] = vertices[1];
        quad.Vertices[2] = vertices[2];
        quad.Vertices[3] = vertices[3];

        m_Quads.push_back(quad);
    }
}

}