#pragma once

#include <functional>
#include <unordered_map>

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
    static EventCallback<TEvent> RegisterEventListener(std::function<void(const TEvent&)> event_callback);

    template<typename TEvent>
    static void RegisterEventListener(const EventCallback<TEvent>& event_callback);
    
    template<typename TEvent>
    static void UnregisterEventListener(const EventCallback<TEvent>& event_callback);

private:
    inline static Callbacks<KeyPressedEvent>          KeyPressedEventCallbacks          = {};
    inline static Callbacks<KeyReleasedEvent>         KeyReleasedEventCallbacks         = {};
    inline static Callbacks<MouseMovedEvent>          MouseMovedEventCallbacks          = {};
    inline static Callbacks<MouseScrolledEvent>       MouseScrolledEventCallbacks       = {};
    inline static Callbacks<MouseButtonPressedEvent>  MouseButtonPressedEventCallbacks  = {};
    inline static Callbacks<MouseButtonReleasedEvent> MouseButtonReleasedEventCallbacks = {};
    inline static Callbacks<WindowResizedEvent>       WindowResizedEventCallbacks       = {};
    inline static Callbacks<WindowClosedEvent>        WindowClosedEventCallbacks        = {};

private:
    template<typename TEvent>
    static void Dispatch(const TEvent& event);

    static void ErrorCallback(int error, const char* description);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void KeyCharCallback(GLFWwindow* window, unsigned int codepoint);
    static void MouseMovedCallback(GLFWwindow* window, double x, double y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrolledCallback(GLFWwindow* window, double x_scroll, double y_scroll);
    static void WindowMovedCallback(GLFWwindow* window, int x, int y);
    static void WindowResizedCallback(GLFWwindow* window, int width, int height);
    static void WindowClosedCallback(GLFWwindow* window);
};

}