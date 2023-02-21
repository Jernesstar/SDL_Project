#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Font.h"

namespace Saddle {

class Text {
private:
    struct CharacterQuad {
        Font::Character character;
        glm::vec2 Vertices[4];
        glm::vec3 Color;
    };

public:
    Text() : m_Text("") { };
    Text(const std::string text, const Font& font) : m_Text(text) { SetText(text, font); };
    ~Text() = default;

    void SetText(const std::string& text, const Font& font);

    std::string GetText() { return m_Text; };

private:
    std::string m_Text;
};

}