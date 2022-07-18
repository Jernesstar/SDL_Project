#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Circle.h"

class PongGame {

public:
    const std::string player_1_name;
    const std::string player_2_name;
    const int SCREEN_WIDTH, SCREEN_HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* paddle_1;
    SDL_Surface* paddle_2;
    
    GameObjects::Circle ball;

public:
    PongGame(const std::string& name_1, const std::string& name_2, SDL_Window*& window, int width, int height);
    ~PongGame();

    void Run();
    void Draw_Circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color);

};