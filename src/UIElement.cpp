#include "UIElement.h"

#include <iostream>

namespace UI {

    UIElement::UIElement() : GameObject()
    {
        
    }

    UIElement::~UIElement()
    {
        GameObject::~GameObject();
    }

}