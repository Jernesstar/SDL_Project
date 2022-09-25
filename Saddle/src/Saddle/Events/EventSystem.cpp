#include "EventSystem.h"

#include <GLFW/glfw3.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Input.h"

#define REGISTER_EVENT_LISTENER(TEvent) \
template<> \
EventCallback<TEvent> EventSystem::RegisterEventListener<TEvent>(const std::function<void(const TEvent&)> event_callback) \
{ \
    Callbacks<TEvent>& list = TEvent##Callbacks; \
    const EventCallback<TEvent> _event_callback(event_callback); \
    list[_event_callback.ID] = _event_callback; \
    return _event_callback; \
} \
 \
template<> \
void EventSystem::RegisterEventListener<TEvent>(const EventCallback<TEvent>& event_callback) \
{ \
    Callbacks<TEvent>& list = TEvent##Callbacks; \
    list[event_callback.ID] = event_callback; \
}

#define UNREGISTER_EVENT_LISTENER(TEvent) \
template<> \
void 

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
DISPATCH(event_type);

namespace Saddle {

ADD_TO_EVENTSYSTEM(KeyPressedEvent);
ADD_TO_EVENTSYSTEM(KeyReleasedEvent);
ADD_TO_EVENTSYSTEM(MouseMovedEvent);
ADD_TO_EVENTSYSTEM(MouseScrolledEvent);
ADD_TO_EVENTSYSTEM(MouseButtonPressedEvent);
ADD_TO_EVENTSYSTEM(MouseButtonReleasedEvent);
ADD_TO_EVENTSYSTEM(WindowResizedEvent);
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

    // Note: Use each of these methods to implement the event system
    /*
    glfwSetCursorEnterCallback
    glfwSetWindowMaximizeCallback
    glfwSetFramebufferSizeCallback
    */
}

void EventSystem::PollEvents() { glfwPollEvents(); }

template<>
void EventSystem::RegisterEventListener<KeyEvent>(const EventCallback<KeyEvent>& event_callback)
{
    RegisterEventListener<KeyPressedEvent>((EventCallback<KeyPressedEvent>&)event_callback);
    RegisterEventListener<KeyReleasedEvent>((EventCallback<KeyReleasedEvent>&)event_callback);
}

template<>
void EventSystem::RegisterEventListener<MouseEvent>(const EventCallback<MouseEvent>& event_callback)
{
    RegisterEventListener<MouseMovedEvent>((EventCallback<MouseMovedEvent>&)event_callback);
    RegisterEventListener<MouseScrolledEvent>((EventCallback<MouseScrolledEvent>&)event_callback);
    RegisterEventListener<MouseButtonPressedEvent>((EventCallback<MouseButtonPressedEvent>&)event_callback);
    RegisterEventListener<MouseButtonReleasedEvent>((EventCallback<MouseButtonReleasedEvent>&)event_callback);
}

template<>
void EventSystem::RegisterEventListener<WindowEvent>(const EventCallback<WindowEvent>& event_callback)
{
    RegisterEventListener<WindowResizedEvent>((EventCallback<WindowResizedEvent>&)event_callback);
    RegisterEventListener<WindowClosedEvent>((EventCallback<WindowClosedEvent>&)event_callback);
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
        Dispatch<KeyPressedEvent>(event);
    }

    if(action == GLFW_RELEASE)
    {
        KeyReleasedEvent event((KeyCode)key);
        Dispatch<KeyReleasedEvent>(event);
    }
}

void EventSystem::KeyCharCallback(GLFWwindow* window, unsigned int codepoint)
{
    // Note: Have a KeyCharEvent
}

void EventSystem::MouseMovedCallback(GLFWwindow* window, double x, double y)
{
    MouseMovedEvent event((float)x, (float)y);
    Dispatch<MouseMovedEvent>(event);
}

void EventSystem::MouseScrolledCallback(GLFWwindow* window, double x_scroll, double y_scroll)
{
    MouseScrolledEvent event((float)x_scroll, (float)y_scroll);
    Dispatch<MouseScrolledEvent>(event);
}

void EventSystem::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        MouseButtonPressedEvent event(button, Input::GetMouseX(), Input::GetMouseY());
        Dispatch<MouseButtonPressedEvent>(event);
    }

    if(action == GLFW_RELEASE)
    {
        MouseButtonReleasedEvent event(button, Input::GetMouseX(), Input::GetMouseY());
        Dispatch<MouseButtonReleasedEvent>(event);
    }
}

void EventSystem::WindowMovedCallback(GLFWwindow* window, int x, int y)
{
    // Note: Have a WindowMovedEvent
}

void EventSystem::WindowResizedCallback(GLFWwindow* window, int width, int height)
{
    WindowResizedEvent event(width, height);
    Dispatch<WindowResizedEvent>(event);
}

void EventSystem::WindowClosedCallback(GLFWwindow* window)
{
    WindowClosedEvent event;
    Dispatch<WindowClosedEvent>(event);
}

}
