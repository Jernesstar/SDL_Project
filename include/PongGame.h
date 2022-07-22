#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Circle.h"
#include "Window.h"

class PongGame {

public:
    const std::string player_1_name;
    const std::string player_2_name;
    const int SCREEN_WIDTH, SCREEN_HEIGHT;

    Saddle::Window window;
    SDL_Surface* paddle_1;
    SDL_Surface* paddle_2;
    
    Saddle::GameObjects::Circle ball;

public:
    PongGame(const std::string& name_1, const std::string& name_2, Saddle::Window& window);
    ~PongGame();

    void Run();
};