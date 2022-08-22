#include "Image.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Saddle/Core/Application.h"

namespace Saddle {

void Image::Init(Uint32 init_flags) { IMG_Init(init_flags); }
void Image::Shutdown() { IMG_Quit(); }

Texture2D Image::Load(const std::string& file_path)
{
    auto renderer = Application::Get().GetWindow().GetRenderer();
    SDL_Surface* surface = IMG_Load(file_path.c_str());

    Texture2D texture(surface);
    SDL_FreeSurface(surface);
    return texture;
}

}