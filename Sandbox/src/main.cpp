#include <Application.h>
#include <Font.h>
#include <Systems.h>

#include "MusicDemo.h"

using namespace Saddle;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

void Start_Screen()
{
    Saddle::Window window = Application::Get().GetWindow();
    std::string title = "Music Demo";
    std::string message = "Press any key to continue";

    Entity title_text;
    Entity message_text;

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

    title_text.AddComponent<EventListenerComponent>(
        [&title_text](SDL_Event& event) { 
            std::cout << "Title was clicked on\n";
        }
    );

    SDL_Event event;
    bool running = true;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            EventListenerSystem::OnEvent(title_text, event);
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    running = false;
                    break;
            }
        }
        auto rect = title_text.GetComponent<RectComponent>();
        auto coord = title_text.GetComponent<Coordinate2DComponent>();
        SDL_Rect sdl_rect = {(int)coord.x, (int)coord.y, (int)rect.width, (int)rect.height};

        SDL_RenderCopy(
            window.GetRenderer(), 
            title_text.GetComponent<TextureComponent>().texture, 
            NULL,
            &sdl_rect
        );

        rect = message_text.GetComponent<RectComponent>();
        coord = message_text.GetComponent<Coordinate2DComponent>();
        sdl_rect = {(int)coord.x, (int)coord.y, (int)rect.width, (int)rect.height};
        SDL_RenderCopy(
            window.GetRenderer(), 
            message_text.GetComponent<TextureComponent>().texture, 
            NULL,
            &sdl_rect
        );

        SDL_RenderPresent(window.GetRenderer());
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
