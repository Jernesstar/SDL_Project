#include "EventSystem.h"

#include <glad/glad.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Input.h"
#include "Saddle/Core/Log.h"


#define GET_CALLBACKS(TEvent) \
template<> \
Callbacks<TEvent>& EventSystem::GetCallbacks<TEvent>() \
{ \
    return TEvent##Callbacks; \
}

namespace Saddle {

GET_CALLBACKS(KeyPressedEvent);
GET_CALLBACKS(KeyReleasedEvent);
GET_CALLBACKS(KeyCharEvent);
GET_CALLBACKS(MouseMovedEvent);
GET_CALLBACKS(MouseScrolledEvent);
GET_CALLBACKS(MouseButtonPressedEvent);
GET_CALLBACKS(MouseButtonReleasedEvent);
GET_CALLBACKS(WindowResizedEvent);
GET_CALLBACKS(WindowMovedEvent);
GET_CALLBACKS(WindowClosedEvent);
GET_CALLBACKS(ApplicationUpdatedEvent);

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

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}

template<>
EventCallback<KeyEvent> EventSystem::RegisterEventListener<KeyEvent>(const std::function<void(const KeyEvent&)>& event_callback)
{
    EventCallback<KeyEvent> _event_callback(event_callback);
    RegisterEventListener<KeyPressedEvent>(_event_callback);
    RegisterEventListener<KeyReleasedEvent>(_event_callback);
    return _event_callback;
}

template<>
void EventSystem::RegisterEventListener<KeyEvent>(const EventCallback<KeyEvent>& event_callback)
{
    RegisterEventListener<KeyPressedEvent>((EventCallback<KeyEvent>)event_callback);
    RegisterEventListener<KeyReleasedEvent>((EventCallback<KeyEvent>)event_callback);
}

template<>
EventCallback<MouseEvent> EventSystem::RegisterEventListener<MouseEvent>(const std::function<void(const MouseEvent&)>& event_callback)
{
    EventCallback<MouseEvent> _event_callback(event_callback);
    RegisterEventListener<MouseMovedEvent>(_event_callback);
    RegisterEventListener<MouseScrolledEvent>(_event_callback);
    RegisterEventListener<MouseButtonPressedEvent>(_event_callback);
    RegisterEventListener<MouseButtonReleasedEvent>(_event_callback);
    return _event_callback;
}

template<>
void EventSystem::RegisterEventListener<MouseEvent>(const EventCallback<MouseEvent>& event_callback)
{
    RegisterEventListener<MouseMovedEvent>((EventCallback<MouseMovedEvent>)event_callback);
    RegisterEventListener<MouseScrolledEvent>((EventCallback<MouseScrolledEvent>)event_callback);
    RegisterEventListener<MouseButtonPressedEvent>((EventCallback<MouseButtonPressedEvent>)event_callback);
    RegisterEventListener<MouseButtonReleasedEvent>((EventCallback<MouseButtonReleasedEvent>)event_callback);
}

template<>
EventCallback<WindowEvent> EventSystem::RegisterEventListener<WindowEvent>(const std::function<void(const WindowEvent&)>& event_callback)
{
    EventCallback<WindowEvent> _event_callback(event_callback);
    RegisterEventListener<WindowResizedEvent>(_event_callback);
    RegisterEventListener<WindowClosedEvent>(_event_callback);
    return _event_callback;
}

template<>
void EventSystem::RegisterEventListener<WindowEvent>(const EventCallback<WindowEvent>& event_callback)
{
    RegisterEventListener<WindowResizedEvent>((EventCallback<WindowResizedEvent>)event_callback);
    RegisterEventListener<WindowClosedEvent>((EventCallback<WindowClosedEvent>)event_callback);
}

template<>
EventCallback<Event> EventSystem::RegisterEventListener<Event>(const std::function<void(const Event&)>& event_callback)
{
    EventCallback<Event> _event_callback(event_callback);
    RegisterEventListener<KeyEvent>(event_callback);
    RegisterEventListener<MouseEvent>(event_callback);
    RegisterEventListener<WindowEvent>(event_callback);
    return _event_callback;
}

template<>
void EventSystem::RegisterEventListener<Event>(const EventCallback<Event>& event_callback)
{
    RegisterEventListener<KeyEvent>((EventCallback<KeyEvent>)event_callback);
    RegisterEventListener<MouseEvent>((EventCallback<MouseEvent>)event_callback);
    RegisterEventListener<WindowEvent>((EventCallback<WindowEvent>)event_callback);
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
        Dispatch(event);
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

void EventSystem::OpenGLMessageCallback(uint32_t source, uint32_t type, uint32_t id, 
    uint32_t severity, int length, const char* message, const void* userParam)
{
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SADDLE_CORE_LOG_ERROR(message);   return;
        case GL_DEBUG_SEVERITY_MEDIUM:       SADDLE_CORE_LOG_ERROR(message);   return;
        case GL_DEBUG_SEVERITY_LOW:          SADDLE_CORE_LOG_WARNING(message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SADDLE_CORE_LOG_INFO(message);    return;
    }
}

}
