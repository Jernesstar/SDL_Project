#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

namespace Saddle {

struct WindowSpecification {
    const std::string Title;
    int Width, Height;
    Uint32 WindowFlags;
    Uint32 RendererFlags;

    WindowSpecification(const std::string& title = "Window", int width = 1200, int height = 640, 
        Uint32 window_flags = 0, Uint32 renderer_flags = 0
    ) : Title(title), Width(width), Height(height), WindowFlags(window_flags), RendererFlags(renderer_flags) { }  
};

class Window {
public:
    int Width, Height;

public:
    Window();
    Window(const WindowSpecification& specs = WindowSpecification());
    ~Window();

    SDL_Window* GetNativeWindow();
    SDL_Renderer* GetRenderer();

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
};

}