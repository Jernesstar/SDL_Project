#pragma once

#include <iostream>

#include <SDL.h>

class UI_Element {

public:
    void Scale(int8_t scalar);
    void Translate(int8_t delta_x, int8_t delta_y);
    void PlaceAt(uint16_t _x, uint16_t _y);
    
    SDL_Texture** GetTexture();
    SDL_Rect* GetRect();

protected: 
    UI_Element();
    ~UI_Element();

    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Point center;
};