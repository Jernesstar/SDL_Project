#pragma once

#include "GameObject.h"

namespace Saddle::UI {
    
class UIElement : public GameObject {

public:
    ~UIElement();
    
protected:
    UIElement();
};

}
