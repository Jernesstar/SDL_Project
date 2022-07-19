#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Window.h"
#include "PongGame.h"
#include "Log.h"
#include "UI.h"

using namespace Saddle;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

Saddle::Window* window;

TTF_Font* pixel_font;

void Start_Screen()
{
    std::string message = "Press any key to continue";
    SDL_Color color = {255, 255, 255};

    UI::Text pong_text("Pong", 10, pixel_font, color, *window->GetRenderer());
    UI::Text message_text("Press any key to continue", 3, pixel_font, color, *window->GetRenderer());

    pong_text.PlaceAt(
        0.5 * SCREEN_WIDTH - pong_text.GetCenter()->x, 
        0.5 * SCREEN_HEIGHT - 2 * pong_text.GetRect()->h
    );

    message_text.PlaceAt(
        0.5 * SCREEN_WIDTH - message_text.GetCenter()->x,
        0.5 * SCREEN_HEIGHT 
    );

    message_text.OnEventClick = [&](SDL_Event& event) {
        std::cout << "Was clicked on" << "\n";
    };

    window->AddUIElement(pong_text);
    window->AddUIElement(message_text);

    SDL_Event event;
    bool running = true;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            window->HandleEvent(event);
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
        window->RenderUI();
    }
}

int main(int argc, char** argv)
{
    window = new Saddle::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong", SDL_INIT_EVENTS);
    pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);

    PongGame game("A", "B", *window->GetWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Start_Screen();

    game.Run();

    TTF_CloseFont(pixel_font);
    delete window;
    return 0;
}