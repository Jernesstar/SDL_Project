#pragma once

#include <functional>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Assert.h"
#include "Event.h"
#include "KeyEvents.h"
#include "MouseEvents.h"
#include "WindowEvents.h"
#include "EventCallback.h"

namespace Saddle {

template<typename TEvent>
using Callbacks = std::unordered_map<UUID, EventCallback<TEvent>>;

class EventSystem {
public:
    static void Init();
    static void PollEvents();

    template<typename TEvent>
    static EventCallback<TEvent> RegisterEventListener(const std::function<void(const TEvent&)>& event_callback)
    {
        Callbacks<TEvent>& list = SelectCallbacks<TEvent>();
        list[event_callback.ID] = event_callback;
    }

    template<typename TEvent>
    static void RegisterEventListener(const EventCallback<TEvent>& event_callback)
    {
        EventCallback<TEvent> _event_callback(event_callback);
        RegisterEventListener<TEvent>(_event_callback);
        return _event_callback;
    }

    template<typename TEvent>
    static void UnregisterEventListener(const EventCallback<TEvent>& event_callback)
    {
        Callbacks<TEvent>& list = SelectCallbacks<TEvent>();
        if(list.count(event_callback.ID))
            list.erase(event_callback.ID);
    }

private:
    inline static Callbacks<KeyPressedEvent>          KeyPressedEventCallbacks          = {};
    inline static Callbacks<KeyReleasedEvent>         KeyReleasedEventCallbacks         = {};
    inline static Callbacks<KeyCharEvent>             KeyCharEventCallbacks             = {};
    inline static Callbacks<MouseMovedEvent>          MouseMovedEventCallbacks          = {};
    inline static Callbacks<MouseScrolledEvent>       MouseScrolledEventCallbacks       = {};
    inline static Callbacks<MouseButtonPressedEvent>  MouseButtonPressedEventCallbacks  = {};
    inline static Callbacks<MouseButtonReleasedEvent> MouseButtonReleasedEventCallbacks = {};
    inline static Callbacks<WindowResizedEvent>       WindowResizedEventCallbacks       = {};
    inline static Callbacks<WindowMovedEvent>         WindowMovedEventCallbacks         = {};
    inline static Callbacks<WindowClosedEvent>        WindowClosedEventCallbacks        = {};

private:
    template<typename TEvent>
    static void Dispatch(const TEvent& event)
    {
        Callbacks<TEvent>& callback_list = SelectCallbacks<TEvent>();
    
        for(auto& [id, func] : callback_list) 
            if(func) func(event); 
    }

    template<typename TEvent>
    static Callbacks<TEvent>& SelectCallbacks();

    static void ErrorCallback(int error, const char* description);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void KeyCharCallback(GLFWwindow* window, uint32_t codepoint);
    static void MouseMovedCallback(GLFWwindow* window, double x, double y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrolledCallback(GLFWwindow* window, double x_scroll, double y_scroll);
    static void WindowResizedCallback(GLFWwindow* window, int width, int height);
    static void WindowMovedCallback(GLFWwindow* window, int x, int y);
    static void WindowClosedCallback(GLFWwindow* window);

    static void OpenGLMessageCallback(uint32_t source, uint32_t type, uint32_t id, 
        uint32_t severity, int length, const char* message, const void* userParam);
};

}