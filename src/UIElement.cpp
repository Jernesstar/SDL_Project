#include "UIElement.h"

namespace UI {

    UIElement::UIElement() : GameObject()
    {
        
    }

    UIElement::~UIElement()
    {
        GameObject::~GameObject();
    }

}