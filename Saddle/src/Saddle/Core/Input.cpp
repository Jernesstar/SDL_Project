#include "Input.h"

#include "Application.h"

namespace Saddle {

bool Input::KeyPressed(KeyCode key)
{   
    // Note: Get the special cases to work
    // Special cases
    if(key == Key::Ctrl) return KeyPressed(Key::LeftCtrl) || KeyPressed(Key::RightCtrl);
    if(key == Key::Shift) return KeyPressed(Key::LeftShift) || KeyPressed(Key::RightShift);
    if(key == Key::Alt) return KeyPressed(Key::LeftAlt) || KeyPressed(Key::RightAlt);

    auto window = Application::Get().GetWindow().GetNativeWindow();
    auto state = glfwGetKey(window, (int)key);

    return state == GLFW_PRESS;
}

void Input::SetCursorMode(CursorMode mode)
{
    GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
}

bool Input::MouseButtonPressed(MouseCode mouse_button)
{
    auto window = Application::Get().GetWindow().GetNativeWindow();
    auto state = glfwGetMouseButton(window, (int)(mouse_button));

    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    auto window = Application::Get().GetWindow().GetNativeWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return { (float)x, (float)y };
}

float Input::GetMouseX() { return GetMousePosition().x; }
float Input::GetMouseY() { return GetMousePosition().y; }

bool Input::KeysPressed(KeyCode key1, KeyCode key2)
{
    if(KeyPressed(key1))
        if(KeyPressed(key2)) return true;
    return false;
}

bool Input::KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3)
{
    if(KeyPressed(key1))
        if(KeyPressed(key2))
            if(KeyPressed(key3)) return true;
    return false;
}

bool Input::KeysPressed(KeyCode key1, KeyCode key2, KeyCode key3, KeyCode key4)
{
    if(KeyPressed(key1))
        if(KeyPressed(key2))
            if(KeyPressed(key3))
                if(KeyPressed(key4)) return true;
    return false;
}

}