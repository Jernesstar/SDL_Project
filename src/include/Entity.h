#pragma once

#include <SDL.h>

class Entity {  
public:
    float x, y;
    SDL_Texture* image;
    Entity() = default;
    Entity(SDL_Renderer* renderer, SDL_Surface* image_surface);
    ~Entity();
};