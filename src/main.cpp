#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Entity.h"
#include "PongGame.h"
#include "Log.h"
#include "Text.h"

#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 1000

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* pixel_font;

void Start_Screen()
{
    std::string message = "Press any key to continue";
    SDL_Color color = {255, 255, 255};

    Text pong_text("Pong", 10, pixel_font, color, renderer);
    Text message_text("Press any key to continue", 3, pixel_font, color, renderer);

    pong_text.rect.x = (0.5 * SCREEN_WIDTH) - pong_text.center.x;
    pong_text.rect.y = (0.5 * SCREEN_HEIGHT) - 2 * pong_text.rect.h;

    message_text.rect.x = (0.5 * SCREEN_WIDTH) - message_text.center.x;
    message_text.rect.y = (0.5 * SCREEN_HEIGHT); 
 
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
        SDL_RenderCopy(renderer, message_text.texture, NULL, &message_text.rect);
        SDL_RenderCopy(renderer, pong_text.texture, NULL, &pong_text.rect);
        SDL_RenderPresent(renderer);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_AUDIO || SDL_INIT_EVENTS);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Pong", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // Creating renderer, renders to above window, first one supporting flags, no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    
    Start_Screen();

    PongGame game("A", "B", window, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Run();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}