#pragma once

#include <glm/mat4x4.hpp>

namespace Saddle {

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);

private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
};

}