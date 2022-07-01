#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Entity.h"
#include "Game.h"
#include "Log.h"
#include "Text.h"

#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 1000

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* pixel_font;

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

void GetAudioSamples(Mix_Chunk* music_samples[], std::string* files, int file_count)
{
    memset(music_samples, 0, sizeof(Mix_Chunk*) * file_count);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, file_count, 1024);

    for(int i = 0; i < file_count; i++)
        music_samples[i] = Mix_LoadWAV(const_cast<char*>(files[i].c_str()));
}

void Start_Screen()
{
    std::string message = "Press any key to continue";
    SDL_Color color = {255, 255, 255};

    Text pong_text("Pong", 10, pixel_font, color, renderer);
    Text message_text("Press any key to continue", 3, pixel_font, color, renderer);

    SDL_Surface* image = IMG_Load("resources/start_bg.png");
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image);

    // std::string file_names[] = {"resources/Kick-Drum.wav", "resources/Snare-Drum.wav"};
    // int files_count = sizeof(file_names) / sizeof(file_names[0]);
    // Mix_Chunk* music_samples[files_count];
    // GetAudioSamples(music_samples, file_names, files_count);

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
        Game game("A", "B", renderer);
        SDL_RenderCopy(renderer, message_text.texture, NULL, &message_text.rect);
        SDL_RenderCopy(renderer, pong_text.texture, NULL, &pong_text.rect);
        SDL_RenderPresent(renderer);
    }

    // for(int i = 0; i <= files_count; i++)
    //     Mix_FreeChunk(music_samples[i]);

    SDL_FreeSurface(image);
    SDL_DestroyTexture(image_texture);
};

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Log::Info("The program is cleaning up", __FILE__, __func__, __LINE__);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    Log::Info("The program is terminating", __FILE__, __func__, __LINE__);

    return 0;
}