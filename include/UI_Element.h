#pragma once

#include <iostream>

#include <SDL.h>

class UI_Element {

public:
    UI_Element();
    ~UI_Element();

    void Translate(uint8_t delta_x, uint8_t delta_y);
    void Scale(uint8_t scalar);
    
    SDL_Texture** GetTexture();
    SDL_Rect* GetRect();

protected: 
    SDL_Texture* texture;
    SDL_Rect rect;
};