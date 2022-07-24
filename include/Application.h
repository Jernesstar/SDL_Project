#pragma once

#include "Window.h"

namespace Saddle {

struct ApplicationSpecification {

    const std::string AppName;
    WindowSpecification Window_Specs;

    ApplicationSpecification(const std::string& app_name, WindowSpecification window_specs)
        : AppName(app_name), Window_Specs(window_specs) { }
};

class Application {

public:


public:
    static void Init(Uint32 sdl_init_flags = SDL_INIT_EVERYTHING, Uint32 img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

private:
    inline static Application* instance;
    Saddle::Window* window;
    const ApplicationSpecification& m_Specification;
    
private:
    Application(const ApplicationSpecification& specification);
    ~Application();
};
    
}
