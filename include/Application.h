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
    static void Init(int sdl_init_flags, int img_init_flags);

private:
    inline static Application* s_Instance;
    Saddle::Window* m_Window;
    const ApplicationSpecification& m_Specification;
    
private:
    Application(const ApplicationSpecification& specification);
    ~Application();
};
    
}
