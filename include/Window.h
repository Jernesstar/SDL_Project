#pragma once

#include <SDL.h>
#include <vector>

#include "GameObject.h"
#include "UI.h"

class Window {

private:
    std::vector<UI::UIElement> ui_elements;
    std::vector<GameObject> game_objects;

public:
    Window();

    void AddUIElement(UI::UIElement _ui_element);
    void RemoveUIElement(UI::UIElement _ui_element);
    
    void RenderUI();
    void RenderGameObjects();
    void RenderScence();

private:
    ~Window();
};