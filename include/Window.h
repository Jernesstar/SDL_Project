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
    const int Width, Height;

public:
    Window();
    Window(int width, int height, const std::string& window_title, Uint32 sdl_init_flags);
    ~Window();

    void AddUIElement(UI::UIElement& element);
    // void RemoveUIElement(UI::UIElement& element);

    void AddGameObject(GameObject& game_object);
    // void RemoveGameObject(GameObject& game_object);
    
    void AddSound(Sound& sound);
    // void RemoveSound(Sound& sound);

    void RenderUI();
    void RenderGameObjects();
    void RenderScene();
    void HandleEvent(SDL_Event& event);

    SDL_Renderer** GetRenderer();
    SDL_Window** GetWindow();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<UI::UIElement*> ui_elements;
    std::vector<GameObject*> game_objects;
    std::vector<Sound*> sounds;

};

}