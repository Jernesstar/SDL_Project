#include "EventSystem.h"

#include <algorithm>

#define REGISTER_EVENT_LISTENER(event_type) \
template<> \
void EventSystem::RegisterEventListener<event_type>(const EventCallback<event_type>& event_callback) \
{ \
    auto& vec = event_type##Callbacks; \
    vec.push_back(event_callback); \
}

namespace Saddle {

void EventSystem::PollEvents()
{
    SDL_PumpEvents();

    SDL_Event SDL_event;
    while(SDL_PollEvent(&SDL_event))
    {
        if(SDL_event.type == SDL_KEYDOWN)
        {
            KeyPressedEvent event((KeyCode)SDL_event.key.keysym.scancode);
            Dispatch<KeyPressedEvent>(PriorityKeyPressedEventCallbacks, event);
            Dispatch<KeyPressedEvent>(KeyPressedEventCallbacks, event);
        }
        if(SDL_event.type == SDL_KEYUP)
        {
            KeyReleasedEvent event((KeyCode)SDL_event.key.keysym.scancode);
            Dispatch<KeyReleasedEvent>(PriorityKeyReleasedEventCallbacks, event);
            Dispatch<KeyReleasedEvent>(KeyReleasedEventCallbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEMOTION)
        {
            MouseMovedEvent event((int)SDL_event.motion.x, (int)SDL_event.motion.y);
            Dispatch<MouseMovedEvent>(PriorityMouseMovedEventCallbacks, event);
            Dispatch<MouseMovedEvent>(MouseMovedEventCallbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEWHEEL)
        {
            MouseScrolledEvent event(SDL_event.wheel.preciseX, SDL_event.wheel.preciseY);
            Dispatch<MouseScrolledEvent>(PriorityMouseScrolledEventCallbacks, event);
            Dispatch<MouseScrolledEvent>(MouseScrolledEventCallbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseButtonPressedEvent event((MouseCode)SDL_event.button.button, (int)SDL_event.button.x, (int)SDL_event.button.y);
            Dispatch<MouseButtonPressedEvent>(PriorityMouseButtonPressedEventCallbacks, event);
            Dispatch<MouseButtonPressedEvent>(MouseButtonPressedEventCallbacks, event);
        }
        if(SDL_event.type == SDL_MOUSEBUTTONUP)
        {
            MouseButtonReleasedEvent event((MouseCode)SDL_event.button.button, (int)SDL_event.button.x, (int)SDL_event.button.y);
            Dispatch<MouseButtonReleasedEvent>(PriorityMouseButtonReleasedEventCallbacks, event);
            Dispatch<MouseButtonReleasedEvent>(MouseButtonReleasedEventCallbacks, event);
        }
        if(SDL_event.type == SDL_WINDOWEVENT)
        {
            if(SDL_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                // On a Window resized event, data1 and data2 will have the new width and height of the window
                WindowResizedEvent event((int)SDL_event.window.data1, (int)SDL_event.window.data2);
                Dispatch<WindowResizedEvent>(PriorityWindowResizedEventCallbacks, event);
                Dispatch<WindowResizedEvent>(WindowResizedEventCallbacks, event);
            }
        }
        if(SDL_event.type == SDL_QUIT)
        {
            WindowClosedEvent event;
            Dispatch<WindowClosedEvent>(PriorityWindowClosedEventCallbacks, event);
            Dispatch<WindowClosedEvent>(WindowClosedEventCallbacks, event);
        }
    }
}

REGISTER_EVENT_LISTENER(KeyPressedEvent);
REGISTER_EVENT_LISTENER(KeyReleasedEvent);
REGISTER_EVENT_LISTENER(MouseMovedEvent);
REGISTER_EVENT_LISTENER(MouseScrolledEvent);
REGISTER_EVENT_LISTENER(MouseButtonPressedEvent);
REGISTER_EVENT_LISTENER(MouseButtonReleasedEvent);
REGISTER_EVENT_LISTENER(WindowResizedEvent);
REGISTER_EVENT_LISTENER(WindowClosedEvent);

template<>
void EventSystem::RegisterEventListener<KeyEvent>(const EventCallback<KeyEvent>& event_callback)
{
    RegisterEventListener<KeyPressedEvent>(event_callback);
    RegisterEventListener<KeyReleasedEvent>(event_callback);
}

template<>
void EventSystem::RegisterEventListener<MouseEvent>(const EventCallback<MouseEvent>& event_callback)
{
    RegisterEventListener<MouseMovedEvent>(event_callback);
    RegisterEventListener<MouseScrolledEvent>(event_callback);
    RegisterEventListener<MouseButtonPressedEvent>(event_callback);
    RegisterEventListener<MouseButtonReleasedEvent>(event_callback);
}

template<>
void EventSystem::RegisterEventListener<WindowEvent>(const EventCallback<WindowEvent>& event_callback)
{
    RegisterEventListener<WindowResizedEvent>(event_callback);
    RegisterEventListener<WindowClosedEvent>(event_callback);
}

template<>
void EventSystem::RegisterEventListener<Event>(const EventCallback<Event>& event_callback)
{
    RegisterEventListener<KeyEvent>(event_callback);
    RegisterEventListener<MouseEvent>(event_callback);
    RegisterEventListener<WindowEvent>(event_callback);
}

void EventSystem::Reset()
{
    KeyPressedEventCallbacks.clear();
    KeyReleasedEventCallbacks.clear();
    MouseMovedEventCallbacks.clear();
    MouseScrolledEventCallbacks.clear();
    MouseButtonPressedEventCallbacks.clear();
    MouseButtonReleasedEventCallbacks.clear();
    WindowResizedEventCallbacks.clear();
    WindowClosedEventCallbacks.clear();
}

}