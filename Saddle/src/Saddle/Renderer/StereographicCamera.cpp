#include "StereographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Saddle/Core/Input.h"

using namespace Saddle;

StereographicCamera::StereographicCamera(float verticalFOV, float nearClip, float farClip)
    : m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
{
    m_ForwardDirection = glm::vec3(0, 0, -1);
    Position = glm::vec3(0, 0, 3);
}

void StereographicCamera::OnUpdate(float ts)
{
    glm::vec2 mousePos = Input::GetMousePosition();
    glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
    m_LastMousePosition = mousePos;

    if (!Input::MouseButtonPressed(Mouse::LeftButton))
    {
        Input::SetCursorMode(CursorMode::Normal);
        return;
    }

    Input::SetCursorMode(CursorMode::Locked);

    bool moved = false;

    constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
    glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

    float speed = 5.0f;

    // Movement
    if (Input::KeyPressed(Key::W))
    {
        Position += m_ForwardDirection * speed * ts;
        moved = true;
    }
    else if (Input::KeyPressed(Key::S))
    {
        Position -= m_ForwardDirection * speed * ts;
        moved = true;
    }
    if (Input::KeyPressed(Key::A))
    {
        Position -= rightDirection * speed * ts;
        moved = true;
    }
    else if (Input::KeyPressed(Key::D))
    {
        Position += rightDirection * speed * ts;
        moved = true;
    }
    if (Input::KeyPressed(Key::Q))
    {
        Position -= upDirection * speed * ts;
        moved = true;
    }
    else if (Input::KeyPressed(Key::E))
    {
        Position += upDirection * speed * ts;
        moved = true;
    }

    // Rotation
    if (delta.x != 0.0f || delta.y != 0.0f)
    {
        float pitchDelta = delta.y * GetRotationSpeed();
        float yawDelta = delta.x * GetRotationSpeed();

        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
            glm::angleAxis(-yawDelta, upDirection)));
        m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

        moved = true;
    }

    if(moved)
    {
        CalculateView();
    }
}

void StereographicCamera::OnResize(uint32_t width, uint32_t height)
{
    if (width == m_ViewportWidth && height == m_ViewportHeight)
        return;

    m_ViewportWidth = width;
    m_ViewportHeight = height;

    CalculateProjection();
}

void StereographicCamera::CalculateProjection()
{
    Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
    InverseProjection = glm::inverse(Projection);
    ViewProjection = Projection * View;
}

void StereographicCamera::CalculateView()
{
    View = glm::lookAt(Position, Position + m_ForwardDirection, glm::vec3(0, 1, 0));
    InverseView = glm::inverse(View);
    ViewProjection = Projection * View;
}
