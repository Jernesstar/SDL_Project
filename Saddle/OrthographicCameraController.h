#pragma once

#include "Saddle/Renderer/OrthographicCamera.h" 
#include <Saddle/Events/Event.h>

namespace Saddle {

class OrthographicCameraController {
public:
	OrthographicCameraController(OrthographicCamera camera);

	void OnUpdate();
	void OnEvent(const Event& event);

private:
	OrthographicCamera m_Camera;
};

}


