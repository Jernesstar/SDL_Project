#pragma once

#include <functional>

#include <SDL.h>

namespace Saddle {
    // The base game object class. Defines some basic fields and methods for all game objects 
class GameObject {  
    
public:
    ~GameObject();
    
    virtual void SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color);

    virtual void Scale(int32_t scalar);
    virtual void Translate(int32_t delta_x, int32_t delta_y);
    virtual void PlaceAt(uint32_t _x, uint32_t _y);
    
    virtual uint32_t GetX();
    virtual uint32_t GetY();
    virtual SDL_Rect* GetRect();
    virtual SDL_Texture** GetTexture();
    virtual SDL_Point* GetCenter();

    // Will handle the incoming and call one of the below function objects if neccessary
    // virtual void HandleEvent(SDL_Event& event);

    // Used to customize behavior when the GameObject is clicked
    std::function<void(SDL_Event&)> OnEventClick;
    std::function<void(SDL_Event&)> OnEventKeyPress;

protected: 
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Point center;
    SDL_Color color;

protected:    
    GameObject();
};

}