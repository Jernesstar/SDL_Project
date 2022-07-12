#pragma once

#include "GameObject.h"

#include <SDL.h>

namespace UI {
class UIElement : public GameObject {

protected:
    UIElement();
    ~UIElement();
};

}