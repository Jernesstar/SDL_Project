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

class EventSystem {
public:
    template<typename TEvent>
    static void RegisterEventListener(const EventCallback<TEvent>& event_callback);

    static void PollEvents();

private:
    inline static std::vector<EventCallback<KeyPressedEvent>> KeyPressedEventCallbacks = {};
    inline static std::vector<EventCallback<KeyReleasedEvent>> KeyReleasedEventCallbacks = {};
    inline static std::vector<EventCallback<MouseMovedEvent>> MouseMovedEventCallbacks = {};
    inline static std::vector<EventCallback<MouseScrolledEvent>> MouseScrolledEventCallbacks = {};
    inline static std::vector<EventCallback<MouseButtonPressedEvent>> MouseButtonPressedEventCallbacks = {};
    inline static std::vector<EventCallback<MouseButtonReleasedEvent>> MouseButtonReleasedEventCallbacks = {};
    inline static std::vector<EventCallback<WindowResizedEvent>> WindowResizedEventCallbacks = {};
    inline static std::vector<EventCallback<WindowClosedEvent>> WindowClosedEventCallbacks = {};

private:
    template<typename TEvent>
    static void Dispatch(std::vector<EventCallback<TEvent>> vector, TEvent& event)
    {
        for(int i = 0; i < vector.size(); i++)
        {
            auto func = vector[i];
            if(func)
                func(event);
        }
    }
};

}