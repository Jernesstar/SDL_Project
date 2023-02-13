#include <ft2build.h>
#include <freetype/freetype.h>

#include <Saddle/Core/Application.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();
    void OnUpdate(TimeStep timeStep) override { }
};

FontDemo::FontDemo() : Application()
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
}