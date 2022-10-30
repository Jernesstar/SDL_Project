#include "OrthographicCameraController.h"

#include "Saddle/Events/EventSystem.h"
#include "Saddle/Core/Input.h"

Saddle::OrthographicCameraController::OrthographicCameraController(OrthographicCamera camera)
	: m_Camera(camera)
{
	EventSystem::RegisterEventListener<Event>(
	[this](const Event& event) -> void {
		this->OnEvent(event);
	});
}

void Saddle::OrthographicCameraController::OnUpdate()
{
	if (Input::KeyPressed(Key::W));
}

void Saddle::OrthographicCameraController::OnEvent(const Event& event)
{
}
