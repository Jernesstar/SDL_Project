#include "GameObject.h"

namespace Saddle {

GameObject::GameObject() 
{
    OnEventClick = [](SDL_Event& event) { };
    OnEventKeyPress = [](SDL_Event& event) { };
}

GameObject::~GameObject()
{
    if(texture)
        SDL_DestroyTexture(texture);
}

void GameObject::OnEvent(SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_x = event.button.x;
        int mouse_y = event.button.y;
        bool x_coord_is_in_bound = rect.x <= mouse_x && mouse_x <= rect.x + rect.w;
        bool y_coord_is_in_bound = rect.y <= mouse_y && mouse_y <= rect.y + rect.h;

        if(x_coord_is_in_bound && y_coord_is_in_bound)
        {
            if(OnEventClick)
                OnEventClick(event);
        }
    }

    else if(event.type == SDL_KEYDOWN)
    {
        if(OnEventKeyPress)
            OnEventKeyPress(event);
    }
}

SDL_Rect& GameObject::GetRect()
{
    return rect;
}

SDL_Texture*& GameObject::GetTexture()
{
    return texture;
}

SDL_Point& GameObject::GetCenter()
{
    return center;
}

}