#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class UI_Element {

public:
    void Translate(uint8_t delta_x, uint8_t delta_y);
    void Scale(uint8_t scalar);
    
    SDL_Texture** GetTexture();
    SDL_Rect* GetRect();

protected: 
    SDL_Texture* texture;
    SDL_Rect rect;

private:
    UI_Element();
    ~UI_Element();
};