#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Application.h"
#include "Window.h"
#include "PongGame.h"
#include "Log.h"
#include "UI.h"
#include "Sound.h"

using namespace Saddle;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

void Start_Screen(Saddle::Window& window)
{
    std::string message = "Press any key to continue";
    TTF_Font* pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    SDL_Color color = {255, 255, 255};

    Sound snare_drum("resources/Snare-Drum.wav");
    Sound kick_drum("resources/Kick-Drum.wav");

    UI::Text pong_text("Pong", pixel_font, 10, color, window.GetRenderer());
    UI::Text message_text("Press any key to continue", pixel_font, 3, color, window.GetRenderer());

    pong_text.PlaceAt(
        0.5 * SCREEN_WIDTH - pong_text.GetCenter().x, 
        0.5 * SCREEN_HEIGHT - 2 * pong_text.GetRect().h
    );

    message_text.PlaceAt(
        0.5 * SCREEN_WIDTH - message_text.GetCenter().x,
        0.5 * SCREEN_HEIGHT 
    );

    pong_text.OnEventClick = [&snare_drum](SDL_Event& event) {
        std::cout << "Title text was clicked on, playing sound..." << "\n";
        snare_drum.Play();
    };

    message_text.OnEventClick = [&kick_drum](SDL_Event& event) {
        std::cout << "Message was clicked on, playing sound..." << "\n";
        kick_drum.Play();
    };
    
    SDL_Event event;
    bool running = true;

    while(running)
    {
        window.AddUIElement(pong_text);
        window.AddUIElement(message_text);
        
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
        window.RenderUI();
    }
    TTF_CloseFont(pixel_font);
}

class App : public Application {

public:
    App() : Application() { }
    ~App() { }

    void Run()
    {
        Start_Screen(m_Window);
        PongGame game("A", "B", m_Window);
        game.Run();
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