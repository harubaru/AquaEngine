#include <graphics/Camera.h>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
        m_Projection = glm::perspective(fov, aspect, zNear, zFar);
        m_pos = pos;
        m_forward = glm::vec3(0, 0, 1);
        m_up = glm::vec3(0, 1, 0);
}

void Camera::Update(float yaw, float pitch, const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
        SetView(yaw, pitch);
        m_Projection = glm::perspective(fov, aspect, zNear, zFar);
        m_pos = pos;
        m_forward = glm::vec3(0, 0, 1);
        m_up = glm::vec3(0, 1, 0);
}

void Camera::SetView(float yaw, float pitch)
{
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_forward = direction;
}
