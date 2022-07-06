#include <iostream>

#include "Entity.h"
#include "Log.h"

Entity::Entity(SDL_Renderer* renderer, SDL_Texture* _texture) 
{
    x, y = (0, 0);
    if(_texture)
        image = SDL_CreateTextureFromSurface(renderer, _texture);
}
Entity::~Entity()
{
    if(texture)
        SDL_DestroyTexture(texture);
};