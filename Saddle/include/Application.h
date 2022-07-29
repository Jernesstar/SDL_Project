#pragma once

#include "Window.h"
#include "Sound.h"

namespace Saddle {

struct ApplicationSpecification {

    std::string AppName;
    Uint32 SDL_Init_Flags;
    Uint32 IMG_Init_Flags;
    WindowSpecification Window_Specification;
    SoundSpecification Sound_Specification;

    ApplicationSpecification(
        const std::string& app_name = "Application", 
        Uint32 sdl_init_flags = SDL_INIT_EVERYTHING, 
        Uint32 img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP,
        WindowSpecification window_specs = WindowSpecification("Application"),
        SoundSpecification sound_specs = SoundSpecification()
    ) : AppName(app_name), SDL_Init_Flags(sdl_init_flags), IMG_Init_Flags(img_init_flags),
        Window_Specification(window_specs), Sound_Specification(sound_specs) { }
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
    ApplicationSpecification s_Specification;

protected:
    Application(const ApplicationSpecification& specs = ApplicationSpecification());

};
    
}
