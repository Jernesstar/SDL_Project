#include "GameObject.h"

GameObject::GameObject() 
{

}

GameObject::~GameObject()
{
    if(texture)
        SDL_DestroyTexture(texture);
}

void GameObject::SetPixel(SDL_Surface*& surface, uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t* target_pixel = (uint32_t*)((uint8_t*)surface->pixels 
                                        + (uint8_t)y * surface->pitch 
                                        + (uint8_t)x * surface->format->BytesPerPixel);
    *target_pixel = color;
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