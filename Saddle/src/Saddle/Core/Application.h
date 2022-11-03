#pragma once

#include "Assert.h"

#include "OpenGL/Window.h"
#include "Layers.h"

int main(int argc, char** argv);

namespace Saddle {

struct ApplicationCommandLineArgs {
    int Count = 0;
    char** Args = nullptr;

    const char* operator[](int index) const
    {
        // SADDLE_CORE_ASSERT(index < Count);
        if(index >= Count)
            return nullptr;
        return Args[index];
    }
};

struct ApplicationSpecification {
    ApplicationCommandLineArgs CommandLineArgs;
    WindowSpecification Window_Specification;

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
    // Note: Remember to remove virtual when done implementing
    virtual void Run();

private:
    inline static Application* s_Instance = nullptr;
    inline static ApplicationSpecification s_Specification;

private:
    static void Init(const ApplicationSpecification& specs = ApplicationSpecification());
    static void Init(const ApplicationCommandLineArgs& args, 
        const ApplicationSpecification& specs = ApplicationSpecification());

protected:
    Window Window;
    uint32_t m_LastFrame = 0;
    LayerStack m_Layers;

    friend int ::main(int argc, char** argv);
};

}
