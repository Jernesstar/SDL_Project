#pragma once

#include <functional>

#include <SDL.h>

namespace Saddle {
    // The base game object class. Defines some basic fields and methods for all game objects 
class GameObject {  
    
public:
    // Used to customize behavior when the GameObject is clicked. Initialize with a lambda function
    std::function<void(SDL_Event&)> OnEventClick;
    // Used to customize behavior when a key is pressed. Initialize with a lambda function
    std::function<void(SDL_Event&)> OnEventKeyPress;

public:
    virtual ~GameObject();
    
    virtual void SetPixel(SDL_Surface* surface, int x, int y, SDL_Color color);
    
    // Will handle the incoming event and call the user-defined functions OnEventClick or OnEventKeyPress if necessary
    virtual void OnEvent(SDL_Event& event);
    
    virtual SDL_Rect& GetRect();
    virtual SDL_Texture*& GetTexture();
    virtual SDL_Point& GetCenter();

protected: 
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Point center;
    SDL_Color color;

protected:    
    GameObject();

};

}