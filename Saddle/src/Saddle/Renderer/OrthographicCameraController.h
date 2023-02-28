#pragma once

#include "Saddle/Renderer/OrthographicCamera.h" 
#include <Saddle/Events/Events.h>
#include <Saddle/Core/Time.h>

namespace Saddle {

class OrthographicCameraController {
public:
    float TranslationSpeed;

public:
    OrthographicCameraController(OrthographicCamera& camera);

    void OnUpdate(TimeStep ts);
    void OnEvent(const MouseScrolledEvent& event);

private:
    OrthographicCamera* m_Camera;
};

}


