#include "StereographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Saddle/Core/Input.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

StereographicCamera::StereographicCamera(float vertical_fov, float near_clip, float far_clip, uint32_t width, uint32_t height)
    : m_ViewportWidth(width), m_ViewportHeight(height)
{
    SetProjection(vertical_fov, near_clip, far_clip);
}

void StereographicCamera::SetProjection(float vertical_fov, float near_clip, float far_clip)
{
    m_VerticalFOV = vertical_fov;
    m_NearClip = near_clip;
    m_FarClip = far_clip;

    SADDLE_CORE_ASSERT(m_ViewportWidth != 0 && m_ViewportHeight != 0, "Viewport width and height must not be 0");
    CalculateProjection();
}

void StereographicCamera::Resize(uint32_t width, uint32_t height)
{
    if(width == m_ViewportWidth && height == m_ViewportHeight)
        return;

    m_ViewportWidth = width;
    m_ViewportHeight = height;

    SADDLE_CORE_ASSERT(m_ViewportWidth != 0 && m_ViewportHeight != 0, "Viewport width and height must not be 0");
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
    View = glm::lookAt(Position, Position + ForwardDirection, glm::vec3(0, 1, 0));
    InverseView = glm::inverse(View);
    ViewProjection = Projection * View;
}

}