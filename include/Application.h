#pragma once

#include "Window.h"

namespace Saddle {

struct ApplicationSpecification {

    std::string AppName;
    Uint32 SDL_Init_Flags;
    Uint32 IMG_Init_Flags;
    WindowSpecification Window_Specification;

    ApplicationSpecification(
        const std::string& app_name = "Application", 
        WindowSpecification window_specs = WindowSpecification("Application"), 
        Uint32 sdl_init_flags = SDL_INIT_EVERYTHING, 
        Uint32 img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP
    ) : AppName(app_name), Window_Specification(window_specs), 
        SDL_Init_Flags(sdl_init_flags), IMG_Init_Flags(img_init_flags) { }
};

class Application {

public:


public:
    static void Init(const ApplicationSpecification& specification = ApplicationSpecification());
    static void Close();

private:
    Saddle::Window* m_Window;
    inline static Application* s_Instance = nullptr;
    inline static ApplicationSpecification* s_Specification;
    
private:
    Application();
    ~Application();
};
    
}
