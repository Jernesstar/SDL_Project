#include "CameraController.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Saddle/Events/EventSystem.h"
#include "Saddle/Core/Input.h"

namespace Saddle {

CameraController::CameraController(Camera& camera, MovementControls controls)
    : m_Camera(&camera), Controls(controls)
{
    EventSystem::RegisterEventListener<ApplicationUpdatedEvent>(
    [this](const ApplicationUpdatedEvent& event) {
        this->OnUpdate(event.DeltaTime);
    });

    // Todo: Get this to work
    // auto callback = EventSystem::RegisterEventListener<MouseEvent>(
    // [this](const MouseEvent& event) {
    //     this->OnMouseEvent(event);
    // });
}

void CameraController::OnUpdate(TimeStep ts)
{
    glm::vec3 position = m_Camera->GetPosition();
    glm::vec3 forward_direction = m_Camera->GetDirection();

    glm::vec2 mousePos = Input::GetMousePosition();
    glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.02f;
    m_LastMousePosition = mousePos;

    bool moved = false;

    const glm::vec3 up_direction(0.0f, 1.0f, 0.0f);
    glm::vec3 rightDirection = glm::cross(forward_direction, up_direction);

    if(Input::KeyPressed(Controls[Control::Forward]))
    {
        position += forward_direction * TranslationSpeed * (float)ts;
        moved = true;
    }
    else if(Input::KeyPressed(Controls[Control::Down]))
    {
        position -= forward_direction * TranslationSpeed * (float)ts;
        moved = true;
    }
    if(Input::KeyPressed(Controls[Control::Left]))
    {
        position -= rightDirection * TranslationSpeed * (float)ts;
        moved = true;
    }
    else if(Input::KeyPressed(Controls[Control::Right]))
    {
        position += rightDirection * TranslationSpeed * (float)ts;
        moved = true;
    }
    if (Input::KeyPressed(Controls[Control::Up]))
    {
        position -= up_direction * TranslationSpeed * (float)ts;
        moved = true;
    }
    else if (Input::KeyPressed(Controls[Control::Down]))
    {
        position += up_direction * TranslationSpeed * (float)ts;
        moved = true;
    }

    // Rotation
    if (delta.x != 0.0f || delta.y != 0.0f)
    {
        float pitchDelta = delta.y * RotationSpeed;
        float yawDelta = delta.x * RotationSpeed;

        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
            glm::angleAxis(-yawDelta, up_direction)));
        forward_direction = glm::rotate(q, forward_direction);

        moved = true;
    }

    m_Camera->SetPosition(position);
    m_Camera->SetDirection(forward_direction);
}

void CameraController::OnMouseEvent(const MouseEvent& event)
{
}

}