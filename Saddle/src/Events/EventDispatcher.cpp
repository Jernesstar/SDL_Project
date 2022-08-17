#include "EventDispatcher.h"

namespace Saddle {

void EventDispatcher::DispatchEvents()
{
    SDL_Event SDL_event;
    while(SDL_PollEvent(&SDL_event))
    {
        if(SDL_event.type == SDL_KEYDOWN)
        {
            KeyPressedEvent event((KeyCode)SDL_event.key.keysym.sym);
            Dispatch<KeyPressedEvent>(key_pressed_event_callbacks, event);
        }
        if(SDL_event.type == SDL_KEYUP)
        {
            KeyReleasedEvent event((KeyCode)SDL_event.key.keysym.sym);
            Dispatch<KeyReleasedEvent>(key_released_event_callbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseButtonPressedEvent event((MouseCode)SDL_event.button.button);
            Dispatch<MouseButtonPressedEvent>(mouse_button_pressed_event_callbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONUP)
        {
            MouseButtonReleasedEvent event((MouseCode)SDL_event.button.button);
            Dispatch<MouseButtonReleasedEvent>(mouse_button_released_event_callbacks, event);
        }
    }
}

template<>
void EventDispatcher::RegisterEventListener<KeyPressedEvent>(std::function<void(KeyPressedEvent&)> event_callback)
{
    key_pressed_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<KeyReleasedEvent>(std::function<void(KeyReleasedEvent&)> event_callback)
{
    key_released_event_callbacks.push_back(event_callback);
}
        
template<>
void EventDispatcher::RegisterEventListener<MouseMovedEvent>(std::function<void(MouseMovedEvent&)> event_callback)
{
    mouse_moved_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<MouseScrolledEvent>(std::function<void(MouseScrolledEvent&)> event_callback)
{
    mouse_scrolled_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<MouseButtonPressedEvent>(std::function<void(MouseButtonPressedEvent&)> event_callback)
{
    mouse_button_pressed_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<MouseButtonReleasedEvent>(std::function<void(MouseButtonReleasedEvent&)> event_callback)
{
    mouse_button_released_event_callbacks.push_back(event_callback);
}

}