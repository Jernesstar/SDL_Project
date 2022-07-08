#include <iostream>

#include "GameObject.h"
#include "Log.h"

GameObject::GameObject(SDL_Texture* _texture) 
{
    rect = {0, 0, 0, 0};

    if(_texture)
        texture = _texture;
}

GameObject::~GameObject()
{
    if(texture)
        SDL_DestroyTexture(texture);
};