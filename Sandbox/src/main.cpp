#include <Application.h>
#include <Font.h>
#include <Systems.h>
#include <Input.h>

#include "MusicDemo.h"

using namespace Saddle;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

void Start_Screen()
{
    Saddle::Window window = Application::Get().GetWindow();
    std::string title = "Music Demo";
    std::string message = "Press any key to continue";

    Scene scene;

    Entity title_text;
    Entity message_text;

    scene.AddEntity(title_text);
    scene.AddEntity(message_text);

    title_text.AddComponent<TextureComponent>();
    message_text.AddComponent<TextureComponent>();

    title_text.AddComponent<RectComponent>();
    message_text.AddComponent<RectComponent>();

    title_text.AddComponent<RGBColorComponent>(255, 255, 255);
    message_text.AddComponent<RGBColorComponent>(255, 255, 255);

    std::string font_path = "Sandbox/resources/pixel_font.ttf";

    Font title_font(font_path, 100);
    TextureSystem::CreateText(title_text, title, title_font);

    Font message_font(font_path, 50);
    TextureSystem::CreateText(message_text, message, message_font);

    title_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - title_text.GetComponent<RectComponent>().width),
        0.5 * SCREEN_HEIGHT - 150
    );
    message_text.AddComponent<Coordinate2DComponent>(
        0.5 * (SCREEN_WIDTH - message_text.GetComponent<RectComponent>().width),
        0.5 * SCREEN_HEIGHT
    );

    title_text.AddComponent<EventListenerComponent>()
    .SetClickEventListener(
        [](SDL_Event& event) {
            std::cout << "This sets the OnClickEvent function object";
        }
    )
    .SetKeyPressEventListener(
        [](SDL_Event& event) {
            std::cout << "This sets the OnEventKeyPress function object";
        }
    );

    bool running = true;

    while(running)
    {
        if(Input::IsKeyPressed(Key::RETURN))
            running = false;
        
        scene.OnSceneRender();
    }
}

class App : public Application {

public:
    App() : Application() { }
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
    Application::Init();

    App app;
    app.Run();

    Application::Close();

    return 0;
}
