#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Saddle {

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

    const glm::vec3& GetPosition() const { return m_Position; }
    float GetRotation() const { return m_Rotation; }

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    float m_Rotation = 0.0f;

private:
    void RecalculateViewMatrix();
};

}