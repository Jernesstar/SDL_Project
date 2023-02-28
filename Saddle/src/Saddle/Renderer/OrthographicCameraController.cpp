#include "OrthographicCameraController.h"

#include "Saddle/Events/EventSystem.h"
#include "Saddle/Core/Input.h"

namespace Saddle {

OrthographicCameraController::OrthographicCameraController(OrthographicCamera& camera)
    : m_Camera(&camera), TranslationSpeed(0.005f)
{
    EventSystem::RegisterEventListener<ApplicationUpdatedEvent>(
    [this](const ApplicationUpdatedEvent& event) {
        this->OnUpdate(event.DeltaTime);
    });

    EventSystem::RegisterEventListener<MouseScrolledEvent>(
    [this](const MouseScrolledEvent& event) {
        this->OnEvent(event);
    });
}

void OrthographicCameraController::OnUpdate(TimeStep ts)
{
    glm::vec3 position = m_Camera->GetPosition();

    if(Input::KeyPressed(Key::W))
        position.y += TranslationSpeed * ts;
    if (Input::KeyPressed(Key::A))
        position.x -= TranslationSpeed * ts;
    if (Input::KeyPressed(Key::S))
        position.y -= TranslationSpeed * ts;
    if (Input::KeyPressed(Key::D))
        position.x += TranslationSpeed * ts;

    m_Camera->SetPosition(position);
}

void OrthographicCameraController::OnEvent(const MouseScrolledEvent& event)
{
}

}