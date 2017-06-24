#ifndef AQUAENGINE_GRAPHICS_CAMERA_H
#define AQUAENGINE_GRAPHICS_CAMERA_H

#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

class Camera {
private:
	glm::mat4 m_Projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	void Update(float yaw, float pitch, const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	void SetView(float yaw, float pitch);

	inline glm::mat4 GetView()
	{
		return glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	inline glm::mat4 GetProjection()
	{
		return m_Projection;
	}

	inline glm::vec3 GetPos()
	{
		return m_pos;
	}
};

#endif
