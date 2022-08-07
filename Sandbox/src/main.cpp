#include <Application.h>
#include <Text.h> 
#include <Font.h>

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
    
    RGBColorComponent color = {255, 255, 255};

    Entity title_text;
    Entity message_text;

    title_text.AddComponent<TextureComponent>();
    message_text.AddComponent<TextureComponent>();

    title_text.AddComponent<RectComponent>();
    message_text.AddComponent<RectComponent>();

    Font title_font(font_path, 20);
    Text::CreateText(title_text, title, title_font, color);

    Font message_font(font_path, 10);
    Text::CreateText(message_text, message, message_font, color);

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
            title_text.GetComponent<TextureComponent>().texture, 
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
