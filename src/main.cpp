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

    UI::Text pong_text("Pong", pixel_font, 10, color, *window->GetRenderer());
    UI::Text message_text("Press any key to continue", pixel_font, 3, color, *window->GetRenderer());

    pong_text.PlaceAt(
        0.5 * SCREEN_WIDTH - pong_text.GetCenter()->x, 
        0.5 * SCREEN_HEIGHT - 2 * pong_text.GetRect()->h
    );

    message_text.PlaceAt(
        0.5 * SCREEN_WIDTH - message_text.GetCenter()->x,
        0.5 * SCREEN_HEIGHT 
    );

    window->AddUIElement(pong_text);
    window->AddUIElement(message_text);

    pong_text.OnEventClick = [](SDL_Event& event) {
        std::cout << "Title text was clicked on" << "\n";
    };

    pong_text.OnEventKeyPress = [](SDL_Event& event) {
        if(event.key.keysym.sym == SDLK_UP)
        {
            std::cout << "The up key was pressed" << "\n";
        }
    };

    message_text.OnEventClick = [](SDL_Event& event) {
        std::cout << "Message was clicked on" << "\n";
    };
    
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

    Start_Screen();

    // PongGame game("A", "B", *window, SCREEN_WIDTH, SCREEN_HEIGHT);
    // game.Run();

    TTF_CloseFont(pixel_font);
    delete window;
    return 0;
}