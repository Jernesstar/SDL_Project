#include "EventDispatcher.h"

#include <algorithm>

namespace Saddle {

void EventDispatcher::PollEvents()
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
        if(SDL_event.type == SDL_MOUSEMOTION)
        {
            MouseMovedEvent event(SDL_event.motion.x, SDL_event.motion.y);
            Dispatch<MouseMovedEvent>(mouse_moved_event_callbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEWHEEL)
        {
            MouseScrolledEvent event(SDL_event.wheel.preciseX, SDL_event.wheel.preciseY);
            Dispatch<MouseScrolledEvent>(mouse_scrolled_event_callbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseButtonPressedEvent event((MouseCode)SDL_event.button.button, SDL_event.button.x, SDL_event.button.y);
            Dispatch<MouseButtonPressedEvent>(mouse_button_pressed_event_callbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONUP)
        {
            MouseButtonReleasedEvent event((MouseCode)SDL_event.button.button, SDL_event.button.x, SDL_event.button.y);
            Dispatch<MouseButtonReleasedEvent>(mouse_button_released_event_callbacks, event);
        }
        if(SDL_event.type == SDL_WINDOWEVENT)
        {
            if(SDL_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                // On a Window resized event, data1 and data2 will have the new width and height of the window
                WindowResizedEvent event((int)SDL_event.window.data1, (int)SDL_event.window.data2);
                Dispatch<WindowResizedEvent>(window_resized_event_callbacks, event);
            }
        }   
        if(SDL_event.type == SDL_QUIT)
        {
            WindowClosedEvent event;
            Dispatch<WindowClosedEvent>(window_closed_event_callbacks, event);
        }
    }
}

// Note: Register callback only if it does not already exist in the list

template<>
void EventDispatcher::RegisterEventListener<KeyPressedEvent>(std::function<void(KeyPressedEvent&)> event_callback)
{
    key_pressed_event_callbacks.push_back(event_callback);
}
// template<>
// void EventDispatcher::UnregisterEventListener<KeyPressedEvent>(std::function<void(KeyPressedEvent&)> event_callback)
// {
//     key_pressed_event_callbacks.erase(std::remove(key_pressed_event_callbacks.begin(), key_pressed_event_callbacks.end(), event_callback), key_pressed_event_callbacks.end());
// }

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

template<>
void EventDispatcher::RegisterEventListener<WindowResizedEvent>(std::function<void(WindowResizedEvent&)> event_callback)
{
    window_resized_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<WindowClosedEvent>(std::function<void(WindowClosedEvent&)> event_callback)
{
    window_closed_event_callbacks.push_back(event_callback);
}

template<>
void EventDispatcher::RegisterEventListener<Event>(std::function<void(Event&)> event_callback)
{
    key_pressed_event_callbacks.push_back(event_callback);
    key_pressed_event_callbacks.push_back(event_callback);
    key_released_event_callbacks.push_back(event_callback);
    mouse_moved_event_callbacks.push_back(event_callback);
    mouse_scrolled_event_callbacks.push_back(event_callback);
    mouse_button_pressed_event_callbacks.push_back(event_callback);
    mouse_button_released_event_callbacks.push_back(event_callback);
    window_resized_event_callbacks.push_back(event_callback);
    window_closed_event_callbacks.push_back(event_callback);
}


}