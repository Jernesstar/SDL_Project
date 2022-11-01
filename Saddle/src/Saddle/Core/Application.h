#pragma once

#include "Assert.h"

#include "OpenGL/Window.h"

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

    // Note: Remember to remove virtual when done implementing
    static void Close();

    virtual Window& GetWindow();
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
    uint32_t m_LastFrame;

    friend int ::main(int argc, char** argv);
};

}
