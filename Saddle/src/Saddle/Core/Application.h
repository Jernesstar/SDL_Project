#pragma once

#include "OpenGL/Window.h"

namespace Saddle {

struct ApplicationSpecification {
    WindowSpecification Window_Specification;
    // AudioSpecification Audio_Specification;

    ApplicationSpecification(
        WindowSpecification window_specs = WindowSpecification()
    ) : Window_Specification(window_specs) { }
};

class Application {
public:
    ~Application();

    static void Init(const ApplicationSpecification& specification = ApplicationSpecification());
    static void Close();
    virtual void Run();

    static Application& Get();
    virtual Window& GetWindow();

private:
    inline static Application* s_Instance = nullptr;

protected:
    inline static const ApplicationSpecification* s_Specification = nullptr;
    Saddle::Window m_Window;

protected:
    Application();
};

}
