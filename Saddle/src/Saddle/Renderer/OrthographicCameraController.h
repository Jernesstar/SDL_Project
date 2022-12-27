#pragma once

#include "Saddle/Renderer/OrthographicCamera.h" 
#include <Saddle/Events/Events.h>
#include <Saddle/Core/Time.h>

namespace Saddle {

class OrthographicCameraController {
public:
    OrthographicCameraController(OrthographicCamera& camera);

    void OnUpdate(TimeStep ts);
    void OnEvent(const MouseScrolledEvent& event);

private:
    OrthographicCamera* m_Camera;

    float m_TranslationSpeed;
};

}


