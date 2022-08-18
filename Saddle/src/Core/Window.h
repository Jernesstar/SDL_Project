#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

namespace Saddle {

struct WindowSpecification {

    const std::string Title;
    int Width, Height;
    Uint32 Flags;

    WindowSpecification(const std::string& title = "Window", int width = 1200, int height = 640, Uint32 flags = 0)
        : Title(title), Width(width), Height(height), Flags(flags) 
    {

    }

};

class Window {

public:
    int Width, Height;

public:
    Window();
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    void HandleEvent(SDL_Event& event);

    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

};

}