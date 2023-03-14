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
        if(index >= Count)
            return nullptr;
        return Args[index];
    }
};

struct ApplicationSpecification {
    ApplicationCommandLineArgs CommandLineArgs;
    WindowSpecification WindowSpecification;

    ApplicationSpecification(
        ApplicationCommandLineArgs commandline_args = { }, 
        Saddle::WindowSpecification window_specs = Saddle::WindowSpecification()
    ) : CommandLineArgs(commandline_args), WindowSpecification(window_specs) { }
};

class Application {
public:
    static void Run();
    static void Close();
    static Application& Get() { return *s_Instance; }

    virtual void OnUpdate(TimeStep ts) = 0;

    Window& GetWindow() { return Window; }
    const ApplicationSpecification& GetSpecification() { return s_Specification; }

private:
    inline static Application* s_Instance = nullptr;
    inline static ApplicationSpecification s_Specification;
    inline static TimePoint s_LastFrame{ Time::GetTime() };

private:
    static void Init(const ApplicationSpecification& specs = ApplicationSpecification());
    static void Init(const ApplicationCommandLineArgs& args, 
        const ApplicationSpecification& specs = ApplicationSpecification());

protected:
    Window Window;

protected:
    Application(const ApplicationSpecification& specs = s_Specification);
    virtual ~Application() = default;

    friend int ::main(int argc, char** argv);
};

}
