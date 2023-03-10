#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

#include "Font.h"

namespace Saddle {

class Text {
private:
    struct CharacterQuad {
        Font::Character Character;
        glm::vec2 Vertices[4];

        void Bind(uint32_t slot) { glBindTextureUnit(slot, Character.TextureID); }
        bool operator ==(const CharacterQuad& other) const { return this->Character.TextureID == other.Character.TextureID; }
    };

public:
    Text() : m_Text("") { }
    Text(const std::string& text, const Font& font, const glm::vec3& color)
        : m_Text(text), m_Color(color) { SetText(text, font, color); }

    ~Text() = default;

    void SetText(const std::string& text, const Font& font, const glm::vec3& color);

    const std::string& GetText() const { return m_Text; }
    const glm::vec3& GetColor() const { return m_Color; }
    const std::vector<CharacterQuad>& GetCharacters() const { return m_Quads; }

    bool operator==(const Text& other) const { return m_Text == other.m_Text && m_Color == other.m_Color; }

private:
    glm::vec3 m_Color;
    std::string m_Text;
    std::vector<CharacterQuad> m_Quads;

    friend class Renderer2D;
};

}