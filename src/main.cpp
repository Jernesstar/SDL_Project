#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 1000

void draw_circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
        }
    }
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    // Create window, centered in the middle of screen, 500 x 500, resizable
    SDL_Window* window = SDL_CreateWindow("Game window", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // Creating renderer, renders to above window, first one supporting flags, no flags
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* pixel_font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* message_surface = TTF_RenderText_Solid(pixel_font, "Welcome to the window!", color);
    SDL_Texture* message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);

    SDL_Surface* image = IMG_Load("resources/start_bg.png");
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image);

    // format: x, y, width, height
    SDL_Rect message_rect = { 128, 256, 500, 40 };
    SDL_Rect image_rect = { 0, 0, 1700, 800 };

    SDL_Point center = { 500, 850 };

    SDL_Event event;
    bool running = true;

    int velocity_x = 0;
    int velocity_y = 0;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            velocity_x = 0;
                            velocity_y = -10;
                            break;
                        case SDLK_DOWN:
                            velocity_x = 0;
                            velocity_y = 10;
                            break;
                        case SDLK_LEFT:
                            velocity_x = -10;
                            velocity_y = 0;
                            break;
                        case SDLK_RIGHT:
                            velocity_x = 10;
                            velocity_y = 0;
                            break;
                    }
            }
        }
        SDL_RenderCopy(renderer, image_texture, NULL, NULL);
        SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);
        
        center.x += velocity_x;
        center.y += velocity_y;
        
        draw_circle(renderer, center, 100, {0, 0, 255});
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(message_surface);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}