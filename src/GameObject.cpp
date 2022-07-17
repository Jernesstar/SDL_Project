#include "GameObject.h"
#include <iostream>

GameObject::GameObject() 
{

}

GameObject::~GameObject()
{
    if(texture)
        SDL_DestroyTexture(texture);
}

void GameObject::SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
    Uint32 pixel_color = SDL_MapRGB(surface->format, color.r, color.g, color.b);
    Uint32* pixel = (Uint32*)((Uint8*)surface->pixels 
                                    + (y * surface->pitch) 
                                    + (x * sizeof(Uint32)));
    *pixel = pixel_color;
}

void GameObject::Scale(int32_t scalar)
{
    
}

void GameObject::Translate(int32_t delta_x, int32_t delta_y)
{
    rect.x += delta_x;
    rect.y += delta_y;
    center.x += delta_x;
    center.y += delta_y;
}

void GameObject::PlaceAt(uint32_t _x, uint32_t _y)
{
    rect.x = _x;
    rect.y = _y;
    int new_center_x = (rect.x + rect.w) * 0.5;
    int new_center_y = (rect.y + rect.h) * 0.5;
    center = {new_center_x, new_center_y};
}

uint32_t GameObject::GetX()
{
    return rect.x;
}

uint32_t GameObject::GetY()
{
    return rect.y;
}

SDL_Rect* GameObject::GetRect()
{
    return &rect;
}

SDL_Texture** GameObject::GetTexture()
{
    return &texture;
}

SDL_Point* GameObject::GetCenter()
{
    return &center;
}