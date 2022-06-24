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

void GetAudioSamples(Mix_Chunk* music_samples[], char* files[], int file_count)
{
    memset(music_samples, 0, sizeof(Mix_Chunk*) * file_count);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(file_count);

    for(int i = 0; i < file_count; i++)
        music_samples[i] = Mix_LoadWAV(files[i]);
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    Mix_Chunk* music_samples[2];
    char* file_names[] = {"resources/Kick-Drum.wav", "resources/Snare-Drum.wav"};
    GetAudioSamples(music_samples, file_names, sizeof(file_names) / sizeof(file_names[0]));

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
    int radius = 100;
    SDL_Color circle_color = { 0, 0, 255};

    SDL_Event event;
    bool running = true;
    int velocity_x = 0;
    int velocity_y = 0;
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
                            velocity_y = -10;
                            break;
                        case SDLK_DOWN:
                            velocity_y = 10;
                            break;
                        case SDLK_LEFT:
                            velocity_x = -10;
                            break;
                        case SDLK_RIGHT:
                            velocity_x = 10;
                            break;
                        case SDLK_RETURN:
                            paused = !paused;
                    }
            }
        }
        SDL_RenderCopy(renderer, image_texture, NULL, NULL);
        SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);
        
        if(center.x + radius >= SCREEN_WIDTH || center.x - radius <= 0)
        {
            if(center.x + radius >= SCREEN_WIDTH) center.x = SCREEN_WIDTH - radius;
            if(center.x - radius <= 0) center.x = radius;
        
            velocity_x *= -1;
            velocity_x += 0.25 * velocity_x;
            Mix_PlayChannel(-1, music_samples[0], 0);
        }
        if(center.y + radius >= SCREEN_HEIGHT || center.y - radius <= 0)
        {
            if(center.y + radius >= SCREEN_HEIGHT) center.y = SCREEN_HEIGHT - radius;
            if(center.y - radius <= 0) center.y = radius;
            
            velocity_y *= -1;
            velocity_y += 0.25 * velocity_y;
            Mix_PlayChannel(-1, music_samples[1], 0);
        }
        if(velocity_x >= 30)
            velocity_x = 10;
        if(velocity_y >= 30)
            velocity_y = 10;

        if(paused == false)
        {
            center.x += velocity_x;
            center.y += velocity_y;
        }
        draw_circle(renderer, center, radius, circle_color);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(message_surface);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(message_texture);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for(int i = 0; i <= 2; i++)
        Mix_FreeChunk(music_samples[i]);

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}