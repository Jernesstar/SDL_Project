#include "UIElement.h"

namespace UI {

UIElement::UIElement() : GameObject()
{
    
}

UIElement::~UIElement()
{
    GameObject::~GameObject();
}

void UIElement::Scale(int32_t scalar)
{
    GameObject::Scale(scalar);
}

void UIElement::Translate(int32_t delta_x, int32_t delta_y)
{
    GameObject::Translate(delta_x, delta_y);
}

void UIElement::PlaceAt(uint32_t _x, uint32_t _y)
{
    GameObject::PlaceAt(_x, _y);
}

SDL_Rect* UIElement::GetRect()
{
    return GameObject::GetRect();
}

SDL_Texture** UIElement::GetTexture()
{
    return GameObject::GetTexture();
}

SDL_Point* UIElement::GetCenter()
{
    return GameObject::GetCenter();
}

}