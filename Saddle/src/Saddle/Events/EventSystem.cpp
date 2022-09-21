#include "EventSystem.h"

#include <GLFW/glfw3.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Input.h"

#define REGISTER_EVENT_LISTENER(event_type) \
template<> \
void EventSystem::RegisterEventListener<event_type>(const EventCallback<event_type>& event_callback) \
{ \
    auto& vec = event_type##Callbacks; \
    vec.push_back(event_callback); \
}

#define DISPATCH(event_type) \
template<> \
void EventSystem::Dispatch<event_type>(event_type& event) \
{ \
    Callbacks<event_type>& priority_callback_list = Priority##event_type##Callbacks; \
    Callbacks<event_type>& callback_list = event_type##Callbacks; \
 \
    for(EventCallback<event_type>& func : priority_callback_list) \
        if(func) func(event); \
 \
    for(EventCallback<event_type>& func : callback_list) \
        if(func) func(event); \
}

namespace Saddle {

REGISTER_EVENT_LISTENER(KeyPressedEvent);
REGISTER_EVENT_LISTENER(KeyReleasedEvent);
REGISTER_EVENT_LISTENER(MouseMovedEvent);
REGISTER_EVENT_LISTENER(MouseScrolledEvent);
REGISTER_EVENT_LISTENER(MouseButtonPressedEvent);
REGISTER_EVENT_LISTENER(MouseButtonReleasedEvent);
REGISTER_EVENT_LISTENER(WindowResizedEvent);
REGISTER_EVENT_LISTENER(WindowClosedEvent);

DISPATCH(KeyPressedEvent);
DISPATCH(KeyReleasedEvent);
DISPATCH(MouseMovedEvent);
DISPATCH(MouseScrolledEvent);
DISPATCH(MouseButtonPressedEvent);
DISPATCH(MouseButtonReleasedEvent);
DISPATCH(WindowResizedEvent);
DISPATCH(WindowClosedEvent);

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

// Note: Implement
void EventSystem::ErrorCallback(int error, const char* description)
{
    SADDLE_CORE_ASSERT(false, description);
}

void EventSystem::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        KeyPressedEvent event((KeyCode)scancode);
        Dispatch<KeyPressedEvent>(event);
    }

    if(action == GLFW_RELEASE)
    {
        KeyReleasedEvent event((KeyCode)scancode);
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
        // Note: Get the coordinates of the mouse
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
