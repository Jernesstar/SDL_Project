#include "Application.h"
#include "MusicDemo.h"

using namespace Saddle;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

void Start_Screen()
{
    Saddle::Window window = Application::Get().GetWindow();
    std::string title = "Music Demo";
    std::string message = "Press any key to continue";

    std::string font_path = "Sandbox/resources/pixel_font.ttf";
    RGBColorComponent color(255, 255, 255);

    Entity title_text;
    Entity message_text;

    title_text.AddComponent<TextComponent>(title, font_path, 8, color);
    message_text.AddComponent<TextComponent>(message, font_path, 5, color);

    title_text.AddComponent<Coordinate2DComponent>(
        0.5 * SCREEN_WIDTH - 10, 
        0.5 * SCREEN_HEIGHT - 50
    );
    message_text.AddComponent<Coordinate2DComponent>(
        0.5 * SCREEN_WIDTH - 10,
        0.5 * SCREEN_HEIGHT
    );

    SDL_Event event;
    bool running = true;

    while(running)
    {

        while(SDL_PollEvent(&event))
        {
            window.HandleEvent(event);
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
