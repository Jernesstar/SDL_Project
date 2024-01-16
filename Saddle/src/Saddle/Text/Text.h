#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

#include "Font.h"

namespace Saddle {

class Text {
public:
    Text() : m_Text("") { }
    Text(const std::string& text, Font* font, const glm::vec4& color = glm::vec4(1.0f))
        : m_Font(font), m_Text(text), m_Color(color) { }
    Text(const std::string& text, Font& font, const glm::vec4& color = glm::vec4(1.0f))
        : m_Font(&font), m_Text(text), m_Color(color) { }
    ~Text() = default;

    void SetFont(Font* font) { m_Font = font; }
    void SetText(const std::string& text) { m_Text = text; }
    void SetColor(const glm::vec4& color) { m_Color = color; }

    Font* GetFont() const { return m_Font; }
    const std::string& GetText() const { return m_Text; }
    const glm::vec4& GetColor() const { return m_Color; }

private:
    Font* m_Font;
    std::string m_Text;
    glm::vec4 m_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
};

}