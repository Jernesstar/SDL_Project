#include <SDL/Font.h>
#include <Saddle/Core/Application.h>
#include <Saddle/Events/Events.h>
#include <Saddle/Core/Input.h>
#include <Saddle/Systems/Systems.h>

#include "MusicDemo.h"

using namespace Saddle;

#define SCREEN_WIDTH Application::Get().GetWindow().Width
#define SCREEN_HEIGHT Application::Get().GetWindow().Height

void Start_Screen()
{
    std::string title = "Music Demo";
    std::string message = "Press any key to continue";

    Scene scene;
    Entity title_text;
    Entity message_text;

    auto& event_listener1 = title_text.AddComponent<EventListenerComponent>();
    event_listener1.OnWindowResized = [&title_text](WindowResizedEvent& event) {
        auto& [x, y] = title_text.GetComponent<Coordinate2DComponent>();
        auto width = title_text.GetComponent<RectComponent>().Width;
        x = 0.5 * (SCREEN_WIDTH - width);
        y = 0.5 * SCREEN_HEIGHT - 150;
    };

    auto& event_listener2 = message_text.AddComponent<EventListenerComponent>();
    event_listener2.OnWindowResized = [&message_text](WindowResizedEvent& event) {
        auto& [x, y] = message_text.GetComponent<Coordinate2DComponent>();
        auto width = message_text.GetComponent<RectComponent>().Width;
        x = 0.5 * (SCREEN_WIDTH - width);
        y = 0.5 * SCREEN_HEIGHT;
    };

    title_text.AddComponent<SoundComponent>("Sandbox/assets/Kick-Drum.wav");
    message_text.AddComponent<SoundComponent>("Sandbox/assets/Snare-Drum.wav");

    title_text.AddComponent<TextureComponent>();
    title_text.AddComponent<RectComponent>();
    title_text.AddComponent<RGBColorComponent>(255, 255, 255);
    message_text.AddComponent<TextureComponent>();
    message_text.AddComponent<RectComponent>();
    message_text.AddComponent<RGBColorComponent>(255, 255, 255);

    std::string font_path = "Sandbox/assets/pixel_font.ttf";
    Font title_font(font_path, 100);
    Font message_font(font_path, 50);

    TextureSystem::CreateText(title_text, title, title_font);
    TextureSystem::CreateText(message_text, message, message_font);

    title_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - title_text.GetComponent<RectComponent>().Width),
        0.5 * SCREEN_HEIGHT - 150
    );
    message_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - message_text.GetComponent<RectComponent>().Width),
        0.5 * SCREEN_HEIGHT
    );

    scene.AddEntity(title_text);
    scene.AddEntity(message_text);

    EventDispatcher::RegisterEventListener<MouseMovedEvent>(
        [](MouseMovedEvent& event) {
            std::cout << "Mouse moved to: " << "[X: " << event.x << "], [Delta Y: " << event.y << "]\n";
        }
    );

    EventDispatcher::RegisterEventListener<MouseScrolledEvent>(
        [](MouseScrolledEvent& event) {
            std::cout << "Mouse scrolled by: " << "[X: " << event.DeltaScrollX << "], [Y: " << event.DeltaScrollY << "]\n"; 
        }
    );

    bool running = true;

    while(running)
    {
        if(Input::AreKeysPressed(Key::Ctrl, Key::Alt, Key::Shift, Key::E))
            running = false;

        EventDispatcher::DispatchEvents();

        scene.OnUpdate();
        scene.OnSceneRender();
    }
}

class App : public Application {

public:
    App(const ApplicationSpecification& specs = ApplicationSpecification()) : Application(specs) { }
    ~App() { }

    void Run()
    {
        Start_Screen();
        MusicDemo demo;
        demo.Run();
    }

};

int main(int argc, char** argv)
{
    WindowSpecification window_specs("Sandbox", 1200, 640, SDL_WINDOW_RESIZABLE);
    ApplicationSpecification app_specs("Sandbox", SDL_INIT_EVENTS, window_specs);

    Application::Init(app_specs);

    App app(app_specs);
    app.Run();

    Application::Close();

    return 0;
}
