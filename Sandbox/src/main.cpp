#include <Application.h>
#include <Font.h>
#include <Systems.h>
#include <Input.h>
#include <Events.h>

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

    title_text.AddComponent<SoundComponent>("Sandbox/assets/Kick-Drum.wav");

    title_text.AddComponent<EventListenerComponent>()
    .MouseButtonPressedEvent = [&title_text](MouseButtonPressedEvent& event) {
        std::cout << "Title Text was clicked. Playing sound\n";
        title_text.GetComponent<SoundComponent>().Sound.Play();
    };
    
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

    EventDispatcher::RegisterEventListener<WindowClosedEvent>(
        [](WindowClosedEvent& event) {
            std::cout << "Application closing\n";
            Application::Close();
        }
    );

    EventDispatcher::RegisterEventListener<WindowResizedEvent>(
        [&title_text, &message_text](WindowResizedEvent& event) {
            std::cout << "New width: " << event.Width << ", New height: " << event.Height << "\n";
            SCREEN_WIDTH = event.Width;
            SCREEN_HEIGHT = event.Height;

            auto& [x1, y1] = title_text.GetComponent<Coordinate2DComponent>();
            auto width1 = title_text.GetComponent<RectComponent>().Width;
            x1 = 0.5 * (SCREEN_WIDTH - width1);
            y1 = 0.5 * SCREEN_HEIGHT - 150;

            auto& [x2, y2] = message_text.GetComponent<Coordinate2DComponent>();
            auto width2 = message_text.GetComponent<RectComponent>().Width;
            x2 = 0.5 * (SCREEN_WIDTH - width2);
            y2 = 0.5 * SCREEN_HEIGHT;
        }
    );

    bool running = true;

    while(running)
    {
        if(Input::IsKeyPressed(Key::LeftCtrl) || Input::IsKeyPressed(Key::RightCtrl))
        {
            if(Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift))
            {
                if(Input::IsKeyPressed(Key::E)) running = false;
            }
        }

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
