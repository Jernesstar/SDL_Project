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

    return state == GLFW_PRESS; // Will return 1 if key was pressed, 0 otherwise
}

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

bool Input::MouseButtonPressed(MouseCode mouse_button)
{
    auto window = Application::Get().GetWindow().GetNativeWindow();
    auto state = glfwGetMouseButton(window, (int)(mouse_button));

    return state == GLFW_PRESS;
}

// bool Input::MousePressedOn(const Rect& rect, const Transform& transform)
// {
//     // Check if the mouse clicked within the rectangle
//     auto& coordinate = transform.Coordinate;
//     auto [mouse_x, mouse_y] = Input::GetMousePosition();
//     bool x_coordinate_is_in_bound = coordinate.x <= mouse_x && mouse_x <= coordinate.x + rect.Width;
//     bool y_coordinate_is_in_bound = coordinate.y <= mouse_y && mouse_y <= coordinate.y + rect.Height;

//     return x_coordinate_is_in_bound && y_coordinate_is_in_bound;
// }

glm::vec2 Input::GetMousePosition()
{
    auto window = Application::Get().GetWindow().GetNativeWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return { (float)x, (float)y };
}

int Input::GetMouseX() { return GetMousePosition().x; }
int Input::GetMouseY() { return GetMousePosition().y; }

}