#pragma once

#include "Assert.h"
#include "Audio.h"
#include "Font.h"
#include "Renderer.h"
#include "Window.h"

namespace Saddle {

struct ApplicationSpecification {
    std::string AppName;
    Uint32 SDL_Init_Flags;
    Uint32 IMG_Init_Flags;
    WindowSpecification Window_Specification;
    AudioSpecification Audio_Specification;

    ApplicationSpecification(
        const std::string& app_name = "Application",
        Uint32 sdl_init_flags = SDL_INIT_EVERYTHING,
        WindowSpecification window_specs = WindowSpecification("Application"),
        AudioSpecification audio_specs = AudioSpecification()
    ) : AppName(app_name), SDL_Init_Flags(sdl_init_flags), Window_Specification(window_specs), 
            Audio_Specification(audio_specs) { }
};

class Application {
public:
    ~Application();

    static void Init(const ApplicationSpecification& specification = ApplicationSpecification());
    static void Close();

    static Application& Get();
    virtual Window& GetWindow();

    virtual void Run();

private:
    inline static Application* s_Instance;

protected:
    Saddle::Window m_Window;
    const ApplicationSpecification s_Specification;

protected:
    Application(const ApplicationSpecification& specs = ApplicationSpecification());
};
    
}
