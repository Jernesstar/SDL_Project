#include <SDL/Font.h>
#include <SDL/Texture2D.h>
#include <Saddle/Core/Application.h>
#include <Saddle/Events/Events.h>
#include <Saddle/Core/Input.h>
#include <Saddle/Systems/Systems.h>

#include "MusicDemo.h"

using namespace Saddle;

#define SCREEN_WIDTH Application::Get().GetWindow().Width
#define SCREEN_HEIGHT Application::Get().GetWindow().Height

bool Start_Screen()
{
    std::string title = "Music Demo";
    std::string message = "Press any key to continue";

    Scene scene;
    Entity title_text;
    Entity message_text;

    title_text.AddComponent<TextureComponent>();
    title_text.AddComponent<RectComponent>();
    title_text.AddComponent<RGBColorComponent>(255, 255, 255);
    message_text.AddComponent<TextureComponent>();
    message_text.AddComponent<RectComponent>();
    message_text.AddComponent<RGBColorComponent>(255, 255, 255);

    std::string font_path = "Sandbox/assets/fonts/pixel_font.ttf";
    Font title_font(font_path, 100);
    Font message_font(font_path, 50);

    TextureSystem::CreateText(title_text, title, title_font);
    TextureSystem::CreateText(message_text, message, message_font);

    title_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - title_text.GetComponent<RectComponent>().Width),
        0.5 * SCREEN_HEIGHT - 150
    );
    title_text.AddComponent<EventListenerComponent>()
    .OnWindowResized = [&title_text](WindowResizedEvent& event) {
        auto& [x, y] = title_text.GetComponent<Coordinate2DComponent>();
        x = 0.5 * (event.Width - title_text.GetComponent<RectComponent>().Width);
        y = 0.5 * event.Height - 150;
    };

    message_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - message_text.GetComponent<RectComponent>().Width),
        0.5 * SCREEN_HEIGHT
    );
    message_text.AddComponent<EventListenerComponent>()
    .OnWindowResized = [&message_text](WindowResizedEvent& event) {
        auto& [x, y] = message_text.GetComponent<Coordinate2DComponent>();
        x = 0.5 * (event.Width - message_text.GetComponent<RectComponent>().Width);
        y = 0.5 * event.Height;
    };

    scene.AddEntity(title_text);
    scene.AddEntity(message_text);

    bool running = true;
    while(running)
    {
        if(Input::IsKeyPressed(Key::Return)) return true;
        if(Input::IsKeyPressed(Key::Escape)) return false;

        EventSystem::PollEvents();

        scene.OnSceneRender();
    }
    return false;
}

class App : public Application {
public:
    App() : Application() { }
    ~App() { }

    void Run()
    {
        bool wants_to_play = Start_Screen();
        if(wants_to_play)
        {
            MusicDemo demo;
            demo.Run();
        }
    }
};

int main(int argc, char** argv)
{
    WindowSpecification window_specs("Sandbox", 1200, 640, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
    ApplicationSpecification app_specs("Sandbox", SDL_INIT_EVENTS | SDL_INIT_VIDEO, 
        IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP, window_specs);

    Application::Init(app_specs);

    App app;
    app.Run();
    
    Application::Close();

    return 0;
}
