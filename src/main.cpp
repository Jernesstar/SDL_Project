#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Entity.h"
#include "PongGame.h"
#include "Log.h"
#include "UI.h"

using namespace UI;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 640

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* pixel_font;

void Start_Screen()
{
    std::string message = "Press any key to continue";
    SDL_Color color = {255, 255, 255};

    Text pong_text("Pong", 10, pixel_font, color, renderer);
    Text message_text("Press any key to continue", 3, pixel_font, color, renderer);

    pong_text.PlaceAt(
        0.5 * SCREEN_WIDTH - pong_text.GetCenter()->x, 
        0.5 * SCREEN_HEIGHT - 2 * pong_text.GetRect()->h
    );

    message_text.PlaceAt(
        0.5 * SCREEN_WIDTH - message_text.GetCenter()->x,
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
        SDL_RenderCopy(renderer, *(message_text.GetTexture()), NULL, message_text.GetRect());
        SDL_RenderCopy(renderer, *(pong_text.GetTexture()), NULL, pong_text.GetRect());
        SDL_RenderPresent(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // Creating renderer, renders to above window, first one supporting flags, no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    
    Start_Screen();

    PongGame game("A", "B", window, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Run();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(pixel_font);

    Mix_CloseAudio();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}