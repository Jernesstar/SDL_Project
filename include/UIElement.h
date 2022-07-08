#pragma once

#include <iostream>

#include <SDL.h>

namespace UI {
    class UIElement {

    public:
        void Scale(int8_t scalar);
        void Translate(int8_t delta_x, int8_t delta_y);
        void PlaceAt(uint16_t _x, uint16_t _y);
        
        SDL_Rect* GetRect();
        SDL_Texture** GetTexture();
        SDL_Point* GetCenter();

    protected: 
        UIElement();
        ~UIElement();

        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_Point center;
    };
}