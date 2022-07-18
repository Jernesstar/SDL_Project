#include "UIElement.h"

#include <iostream>

namespace Saddle::UI {

UIElement::UIElement() : GameObject()
{
    
}

UIElement::~UIElement()
{
    GameObject::~GameObject();
}

}