#pragma once

#include <string>
#include <functional>
#include <vector>

#include <GLFW/glfw3.h>

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
    static void Init();
    static void PollEvents();
    static void Reset();

    template<typename TEvent>
    static void RegisterEventListener(const EventCallback<TEvent>& event_callback);

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
    static void Dispatch(TEvent& event);

    static void ErrorCallback(int error, const char* description);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void KeyCharCallback(GLFWwindow* window, unsigned int codepoint);
    static void MouseMovedCallback(GLFWwindow* window, double x, double y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrolledCallback(GLFWwindow* window, double x_scroll, double y_scroll);
    static void WindowMovedCallback(GLFWwindow* window, int x, int y);
    static void WindowResizedCallback(GLFWwindow* window, int width, int height);
    static void WindowClosedCallback(GLFWwindow* window);

    friend class Application;
    friend class Window;
};

}