#include <iostream>

#include "Entity.h"
#include "Log.h"

Entity::Entity(SDL_Renderer* renderer, SDL_Surface* image_surface) 
{
    x, y = (0, 0);
    image = nullptr;
    if(image_surface)
        image = SDL_CreateTextureFromSurface(renderer, image_surface);
    Log::Warning("Image has already been destroyed", __FILE__, __func__, __LINE__);
}
Entity::~Entity()
{
    if(image)
        SDL_DestroyTexture(image);
};