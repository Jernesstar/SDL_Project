#include <iostream>

#include "Entity.h"
#include "Log.h"

Entity::Entity(SDL_Renderer* renderer, SDL_Texture* _texture) 
{
    rect = {0, 0, 0, 0};

    if(_texture)
        texture = _texture;
}
Entity::~Entity()
{
    if(texture)
        SDL_DestroyTexture(texture);
};