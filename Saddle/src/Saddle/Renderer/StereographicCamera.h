#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Camera.h"

namespace Saddle {

class StereographicCamera : public Camera {
public:
    StereographicCamera(float verticalFOV, float nearClip, float farClip);

    void OnUpdate(float ts);
    void OnResize(uint32_t width, uint32_t height);

    const glm::vec3& GetDirection() const { return m_ForwardDirection; }
    float GetRotationSpeed() { return m_RotationSpeed; }

    void SetProjection(float verticalFOV, float nearClip, float farClip);

private:
    void CalculateView() override;
    void CalculateProjection() override;

private:
    float m_VerticalFOV = 45.0f;
    float m_NearClip = 0.1f;
    float m_FarClip = 100.0f;
    float m_RotationSpeed = 0.3f;

    glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };

    glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };

    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};

}