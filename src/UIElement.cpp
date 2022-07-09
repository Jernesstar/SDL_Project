#include "UIElement.h"

namespace UI {
    
    UIElement::UIElement() : GameObject()
    {
        
    }

    UIElement::~UIElement()
    {
        GameObject::~GameObject();
    }

    void UIElement::Scale(int8_t scalar)
    {
        GameObject::Scale(scalar);
    }

    void UIElement::Translate(int8_t delta_x, int8_t delta_y)
    {
        GameObject::Translate(delta_x, delta_y);
    }

    void UIElement::PlaceAt(uint16_t _x, uint16_t _y)
    {
        GameObject::PlaceAt(_x, _y);
    }

    SDL_Rect* UIElement::GetRect()
    {
        return &rect;
    }

    SDL_Texture** UIElement::GetTexture()
    {
        return &texture;
    }

    SDL_Point* UIElement::GetCenter()
    {
        return &center;
    }
}