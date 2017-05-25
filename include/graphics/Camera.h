#ifndef AQUAGL_CAMERA_H
#define AQUAGL_CAMERA_H

#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

class Camera {
private:
	glm::mat4 m_Projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_Projection = glm::perspective(fov, aspect, zNear, zFar);
		m_pos = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetView()
	{
		return glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	inline glm::mat4 GetProjection()
	{
		return m_Projection;
	}
};

#endif

