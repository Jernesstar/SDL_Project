#pragma once

#include <SDL.h>

class Entity {  

public:
    float x, y;
    SDL_Texture* texture;
    SDL_Rect rect;

    Entity() = default;
    Entity(SDL_Renderer* renderer, SDL_Texture* _texture);
    ~Entity();
};