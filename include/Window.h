#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "UI.h"
#include "Sound.h"

namespace Saddle {

class Window {

public:
    Window(int width, int height, const std::string& window_title, Uint32 sdl_init_flags);
    ~Window();

    template<typename T>
    void AddElement(const T& element);
    
    template<typename T>
    void RemoveElement(const T& element);

    void RenderUI();
    void RenderGameObjects();
    void RenderScene();
    void HandleEvent(SDL_Event& event);

    SDL_Renderer** GetRenderer();
    SDL_Window** GetWindow();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<UI::UIElement> ui_elements;
    std::vector<GameObject> game_objects;
    std::vector<Sound> sounds;

};

}