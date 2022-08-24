#include "Image.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Saddle/Core/Application.h"

namespace Saddle {

void Image::Init(Uint32 init_flags) { IMG_Init(init_flags); }
void Image::Shutdown() { IMG_Quit(); }

Texture2D Image::Load(const std::string& file_path)
{
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    Texture2D texture(surface);
    SDL_FreeSurface(surface);
    return texture;
}

Texture2D Image::Load(const std::string& file_path, int width, int height, int angle)
{
    Texture2D texture = Load(file_path);
    texture.Width = width;
    texture.Height = height;
    texture.Angle = angle;
    return texture;
}

}