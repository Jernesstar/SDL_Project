#include "GameObject.h"

GameObject::GameObject() 
{

}

GameObject::~GameObject()
{
    if(texture)
        SDL_DestroyTexture(texture);
}

void GameObject::Scale(int8_t scalar)
{
    
}

void GameObject::Translate(int8_t delta_x, int8_t delta_y)
{
    rect.x += delta_x;
    rect.y += delta_y;
    center.x += delta_x;
    center.y += delta_y;
}

void GameObject::PlaceAt(uint16_t _x, uint16_t _y)
{
    rect.x = _x;
    rect.y = _y;
    int new_center_x = (rect.x + rect.w) * 0.5;
    int new_center_y = (rect.y + rect.h) * 0.5;
    center = {new_center_x, new_center_y};
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