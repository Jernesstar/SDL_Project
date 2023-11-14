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
    Saddle::WindowSpecification WindowSpecification;

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

    Window& GetWindow() { return m_Window; }
    const ApplicationSpecification& GetSpecification() { return s_Specification; }

    static TimeStep GetTimeStep() { return s_TimeStep; }

private:
    Saddle::Window m_Window;

    inline static Application* s_Instance = nullptr;
    inline static ApplicationSpecification s_Specification;
    inline static TimePoint s_LastFrame{ Time::GetTime() };
    inline static TimeStep s_TimeStep;

private:
    static void Init(const ApplicationSpecification& specs = ApplicationSpecification());
    static void Init(const ApplicationCommandLineArgs& args, 
        const ApplicationSpecification& specs = ApplicationSpecification());

protected:
    Application(const ApplicationSpecification& specs = s_Specification);
    virtual ~Application() = default;

    friend int ::main(int argc, char** argv);
};

}