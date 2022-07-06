#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
// #include <SDL_mixer.h>

#include "PongGame.h"
#include "Text.h"
#include "Entity.h"
#include "Log.h"

PongGame::PongGame(std::string name_1, std::string name_2, SDL_Window* _window, int width, int height) 
: player_1_name(name_1), player_2_name(name_2), SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{  
    window = _window;
    renderer = SDL_GetRenderer(_window);

    paddle_1 = (SDL_Surface*)malloc(sizeof(SDL_Surface));
    paddle_2 = (SDL_Surface*)malloc(sizeof(SDL_Surface));

    int flags, paddle_width, paddle_height, depth;
    flags = 0;
    paddle_width = 10;
    paddle_height = 500;
    depth = 32;
    paddle_1 = SDL_CreateRGBSurface(flags, paddle_width, paddle_height, depth, 0, 0, 0, 0);

    SDL_FillRect(paddle_1, NULL, SDL_MapRGB(paddle_1->format, 255, 255, 255)); 
}

PongGame::~PongGame()
{
    SDL_FreeSurface(paddle_1);
    SDL_FreeSurface(paddle_2);  
}

void PongGame::Draw_Circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy *dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
            }
       }
   }
}

void PongGame::GetAudioSamples(Mix_Chunk* music_samples[], std::string* files, int file_count)
{
    memset(music_samples, 0, sizeof(Mix_Chunk*) * file_count);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, file_count, 1024);

    for(int i = 0; i < file_count; i++)
        music_samples[i] = Mix_LoadWAV(const_cast<char*>(files[i].c_str()));
}

void PongGame::Run()
{
    int radius = 20;
    SDL_Color circle_color = { 0, 255, 0 };

    paddle_1->clip_rect.x = SCREEN_WIDTH / 4;
    paddle_1->clip_rect.y = SCREEN_HEIGHT / 2;
    SDL_Point center = { 700, paddle_1->clip_rect.y + 30 };

    SDL_Surface* screen = SDL_GetWindowSurface(window);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, paddle_1);

    SDL_Event event;
    bool running = true;
    int velocity_x = -15;
    int velocity_y = 15;
    bool paused = false;

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
                            if(paddle_1->clip_rect.y > 0)
                                paddle_1->clip_rect.y += -30;
                            break;
                        case SDLK_DOWN:
                            if(paddle_1->clip_rect.y < SCREEN_HEIGHT)
                                paddle_1->clip_rect.y += 30;
                            break;
                        case SDLK_RETURN:
                            paused = !paused;
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;
            }
        }

        if(center.x - radius <= paddle_1->clip_rect.x + paddle_1->clip_rect.w
            && center.x - radius >= paddle_1->clip_rect.x)
        {
            if(center.y <= paddle_1->clip_rect.y + paddle_1->clip_rect.h && center.y >= paddle_1->clip_rect.y)
                velocity_x *= -1;
        }
        if(center.x + radius >= SCREEN_WIDTH || center.x - radius <= 0)
        {
            if(center.x + radius >= SCREEN_WIDTH) center.x = SCREEN_WIDTH - radius;
            else if(center.x - radius <= 0) center.x = radius;

            velocity_x *= -1;
        }
        if(center.y + radius >= SCREEN_HEIGHT || center.y - radius <= 0)
        {
            // Circle is touching the top of the screen, thus set the center of the circle to be a radius higher than the bottom of the screen
            if(center.y + radius >= SCREEN_HEIGHT) center.y = SCREEN_HEIGHT - radius;
            // Circle is touching the bottom of the screen, thus set the center to the radius exactly
            else if(center.y - radius <= 0) center.y = radius;

            velocity_y *= -1;
        }
        if(paused == false)
        {
            center.x += velocity_x;
            center.y += velocity_y;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Draw_Circle(renderer, center, radius, circle_color);
        SDL_RenderCopy(renderer, texture, NULL, &(paddle_1->clip_rect));

        SDL_RenderPresent(renderer);
    }
}