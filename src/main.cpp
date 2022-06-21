#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1028
#define SCREEN_HEIGHT 512

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    // Create window, centered in the middle of screen, 500 x 500, resizable
    SDL_Window* window = SDL_CreateWindow("Game window", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // Creating renderer, renders to above window, first one supporting flags, no flags
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    SDL_Color color = {0, 255, 0};
    SDL_Surface* message_surface = TTF_RenderText_Solid(pixel_font, "Welcome to the window!", color);
    SDL_Texture* message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);

    SDL_Rect message_rect;
    message_rect.w = 300;
    message_rect.h = 40;
    message_rect.x = 128;
    message_rect.y = 256;

    SDL_Event event;
    bool running = true;
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(message_surface);
    SDL_DestroyTexture(message_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
