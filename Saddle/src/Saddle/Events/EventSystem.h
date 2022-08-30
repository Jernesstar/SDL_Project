#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include <SDL.h>

#include "Assert.h"
#include "Event.h"
#include "KeyEvents.h"
#include "MouseEvents.h"
#include "WindowEvents.h"

namespace Saddle {

template<typename TEvent>
using EventCallback = std::function<void(TEvent&)>;

template<typename TEvent>
using Callbacks = std::vector<EventCallback<TEvent>>;

class EventSystem {
public:
    template<typename TEvent>
    static void RegisterEventListener(const EventCallback<TEvent>& event_callback);

    static void Reset();

    static void PollEvents();

private:
    inline static Callbacks<KeyPressedEvent>          KeyPressedEventCallbacks          = {};
    inline static Callbacks<KeyReleasedEvent>         KeyReleasedEventCallbacks         = {};
    inline static Callbacks<MouseMovedEvent>          MouseMovedEventCallbacks          = {};
    inline static Callbacks<MouseScrolledEvent>       MouseScrolledEventCallbacks       = {};
    inline static Callbacks<MouseButtonPressedEvent>  MouseButtonPressedEventCallbacks  = {};
    inline static Callbacks<MouseButtonReleasedEvent> MouseButtonReleasedEventCallbacks = {};
    inline static Callbacks<WindowResizedEvent>       WindowResizedEventCallbacks       = {};
    inline static Callbacks<WindowClosedEvent>        WindowClosedEventCallbacks        = {};

    inline static Callbacks<KeyPressedEvent>          PriorityKeyPressedEventCallbacks          = {};
    inline static Callbacks<KeyReleasedEvent>         PriorityKeyReleasedEventCallbacks         = {};
    inline static Callbacks<MouseMovedEvent>          PriorityMouseMovedEventCallbacks          = {};
    inline static Callbacks<MouseScrolledEvent>       PriorityMouseScrolledEventCallbacks       = {};
    inline static Callbacks<MouseButtonPressedEvent>  PriorityMouseButtonPressedEventCallbacks  = {};
    inline static Callbacks<MouseButtonReleasedEvent> PriorityMouseButtonReleasedEventCallbacks = {};
    inline static Callbacks<WindowResizedEvent>       PriorityWindowResizedEventCallbacks       = {};
    inline static Callbacks<WindowClosedEvent>        PriorityWindowClosedEventCallbacks        = {};

private:
    template<typename TEvent>
    static void Dispatch(Callbacks<TEvent>& vector, TEvent& event)
    {
        for(int i = 0; i < vector.size(); i++)
        {
            auto func = vector[i];
            if(func)
                func(event);
        }
    }

    friend class Application;
    friend class Window;
};

}