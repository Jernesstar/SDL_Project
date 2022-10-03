#pragma once

#include "OpenGL/Window.h"

int main();

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
    Application();
    ~Application() = default;

    static Application& Get();
    static void Close();

    virtual Window& GetWindow();
    virtual void Run() = 0;

private:
    inline static Application* s_Instance = nullptr;
    inline static const ApplicationSpecification* s_Specification = nullptr;

private:
    static void Init(const ApplicationSpecification& specification = ApplicationSpecification());

protected:
    Window Window;

    friend int ::main();
};

}
