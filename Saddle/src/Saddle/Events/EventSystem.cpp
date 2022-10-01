#include "EventSystem.h"

#include <iostream>

#include <GLFW/glfw3.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Input.h"
#include "Saddle/Core/Log.h"

#define REGISTER_EVENT_LISTENER(TEvent) \
template<> \
void EventSystem::RegisterEventListener<TEvent>(const EventCallback<TEvent>& event_callback) \
{ \
    Callbacks<TEvent>& list = TEvent##Callbacks; \
    list[event_callback.ID] = event_callback; \
} \
template<> \
EventCallback<TEvent> EventSystem::RegisterEventListener<TEvent>(const std::function<void(const TEvent&)> event_callback) \
{ \
    EventCallback<TEvent> _event_callback(event_callback); \
    RegisterEventListener<TEvent>((EventCallback<TEvent>&)_event_callback); \
    return _event_callback; \
}

#define UNREGISTER_EVENT_LISTENER(TEvent) \
template<> \
void EventSystem::UnregisterEventListener<TEvent>(const EventCallback<TEvent>& event_callback) \
{ \
    Callbacks<TEvent>& list = TEvent##Callbacks; \
    if(list.count(event_callback.ID)) \
        list.erase(event_callback.ID); \
} \

#define DISPATCH(event_type) \
template<> \
void EventSystem::Dispatch<event_type>(const event_type& event) \
{ \
    Callbacks<event_type>& callback_list = event_type##Callbacks; \
 \
    for(auto& [id, func] : callback_list) \
        if(func) func(event); \
}

#define ADD_TO_EVENTSYSTEM(event_type) \
REGISTER_EVENT_LISTENER(event_type); \
DISPATCH(event_type); \
UNREGISTER_EVENT_LISTENER(event_type); \

namespace Saddle {

ADD_TO_EVENTSYSTEM(KeyPressedEvent);
ADD_TO_EVENTSYSTEM(KeyReleasedEvent);
ADD_TO_EVENTSYSTEM(KeyCharEvent);
ADD_TO_EVENTSYSTEM(MouseMovedEvent);
ADD_TO_EVENTSYSTEM(MouseScrolledEvent);
ADD_TO_EVENTSYSTEM(MouseButtonPressedEvent);
ADD_TO_EVENTSYSTEM(MouseButtonReleasedEvent);
ADD_TO_EVENTSYSTEM(WindowResizedEvent);
ADD_TO_EVENTSYSTEM(WindowMovedEvent);
ADD_TO_EVENTSYSTEM(WindowClosedEvent);

void EventSystem::Init()
{
    GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();

    SADDLE_CORE_ASSERT(window);

    glfwSetErrorCallback(ErrorCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCharCallback(window, KeyCharCallback);
    glfwSetCursorPosCallback(window, MouseMovedCallback);
    glfwSetScrollCallback(window, MouseScrolledCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetWindowPosCallback(window, WindowMovedCallback);
    glfwSetWindowSizeCallback(window, WindowResizedCallback);
    glfwSetWindowCloseCallback(window, WindowClosedCallback);
}

void EventSystem::PollEvents() { glfwPollEvents(); }

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
    RegisterEventListener<KeyEvent>((EventCallback<KeyEvent>&)event_callback);
    RegisterEventListener<MouseEvent>((EventCallback<MouseEvent>&)event_callback);
    RegisterEventListener<WindowEvent>((EventCallback<WindowEvent>&)event_callback);
}

void EventSystem::ErrorCallback(int error, const char* description)
{
    SADDLE_CORE_ASSERT(false, description);
}

void EventSystem::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        KeyPressedEvent event((KeyCode)key);
        Dispatch(event);
    }

    if(action == GLFW_RELEASE)
    {
        KeyReleasedEvent event((KeyCode)key);
        Dispatch(event);
    }

    if(action == GLFW_REPEAT)
    {
        KeyPressedEvent event((KeyCode)key, true);
    }
}


void EventSystem::KeyCharCallback(GLFWwindow* window, unsigned int codepoint)
{
    KeyCharEvent event((KeyCode)codepoint, (char)codepoint);
    Dispatch(event);
}

void EventSystem::MouseMovedCallback(GLFWwindow* window, double x, double y)
{
    MouseMovedEvent event((float)x, (float)y);
    Dispatch(event);
}

void EventSystem::MouseScrolledCallback(GLFWwindow* window, double x_scroll, double y_scroll)
{
    MouseScrolledEvent event((float)x_scroll, (float)y_scroll);
    Dispatch(event);
}

void EventSystem::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        MouseButtonPressedEvent event((MouseCode)button, Input::GetMouseX(), Input::GetMouseY());
        Dispatch(event);
    }

    if(action == GLFW_RELEASE)
    {
        MouseButtonReleasedEvent event((MouseCode)button, Input::GetMouseX(), Input::GetMouseY());
        Dispatch(event);
    }
}

void EventSystem::WindowResizedCallback(GLFWwindow* window, int width, int height)
{
    WindowResizedEvent event(width, height);
    Dispatch(event);
}

void EventSystem::WindowMovedCallback(GLFWwindow* window, int x, int y)
{
    WindowMovedEvent event(x, y);
    Dispatch(event);
}
void EventSystem::WindowClosedCallback(GLFWwindow* window)
{
    WindowClosedEvent event;
    Dispatch(event);
}

}
