#pragma once

#include <SDL.h>

class GameObject {  

protected:
    SDL_Texture* texture;
    SDL_Rect rect;

    GameObject(SDL_Texture* _texture);
    ~GameObject();
};