#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Text.h"
#include "Entity.h"

Game::Game(std::string name_1, std::string name_2, SDL_Renderer* _renderer) 
: player_1_name(name_1), player_2_name(name_2)
{  
    renderer = _renderer;
    
    TTF_Font* font = TTF_OpenFont("resources/pixel_font.ttf", 15);
    
    Text text_1 = Text(name_1, 10, font, SDL_Color({255, 255, 255}), _renderer);
    Text text_2 = Text(name_2, 10, font, SDL_Color({255, 255, 255}), _renderer);

    SDL_RenderCopy(_renderer, text_1.texture, NULL, &text_1.rect);
    SDL_RenderCopy(_renderer, text_2.texture, NULL, &text_2.rect);
}

Game::~Game()
{
    
}