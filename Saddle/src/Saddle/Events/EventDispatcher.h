#pragma once

#include <iostream>
#include <functional>
#include <vector>

#include <SDL.h>

#include "Event.h"
#include "KeyEvents.h"
#include "MouseEvents.h"
#include "ApplicationEvents.h"
#include "Assert.h"

namespace Saddle {

class EventDispatcher {
public:
    template<typename TEvent>
    static void RegisterEventListener(std::function<void(TEvent&)> event_callback);

    template<typename TEvent>
    static void UnregisterEventListener(std::function<void(TEvent&)> event_callback);

    static void PollEvents();

private:
    inline static std::vector<std::function<void(KeyPressedEvent&)>> key_pressed_event_callbacks = {};
    inline static std::vector<std::function<void(KeyReleasedEvent&)>> key_released_event_callbacks = {};
    inline static std::vector<std::function<void(MouseMovedEvent&)>> mouse_moved_event_callbacks = {};
    inline static std::vector<std::function<void(MouseScrolledEvent&)>> mouse_scrolled_event_callbacks = {};
    inline static std::vector<std::function<void(MouseButtonPressedEvent&)>> mouse_button_pressed_event_callbacks = {};
    inline static std::vector<std::function<void(MouseButtonReleasedEvent&)>> mouse_button_released_event_callbacks = {};
    inline static std::vector<std::function<void(WindowResizedEvent&)>> window_resized_event_callbacks = {};
    inline static std::vector<std::function<void(WindowClosedEvent&)>> window_closed_event_callbacks = {};

private:
    template<typename T>
    static void Dispatch(std::vector<std::function<void(T&)>> vector, T& event)
    {
        for(auto func : vector)
        {
            func(event);
        }
    }
};

}