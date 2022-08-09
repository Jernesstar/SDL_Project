#include "Utils.h"

namespace Saddle
{
    void SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
    {
        Uint32 pixel_color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
        Uint32* pixel = (Uint32*)((Uint8*)surface->pixels 
                                        + (y * surface->pitch) 
                                        + (x * surface->format->BitsPerPixel));
        *pixel = pixel_color;
    }
}