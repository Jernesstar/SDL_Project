#include <iostream>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create window, centered in the middle of screen, 500 x 500, resizable
    SDL_Window* window = SDL_CreateWindow("Game window", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // Creating renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
