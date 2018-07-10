#ifndef AQUAENGINE_GRAPHICS_CAMERA_H
#define AQUAENGINE_GRAPHICS_CAMERA_H

#include <export.h>

#include <graphics/Display.h>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>
#include <core/Input.h>

class API Camera {
private:
	glm::mat4 m_Projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_right;
	glm::vec3 m_up;
	bool m_CursorLocked;
	float m_MouseSensitivity;
	float m_HorizAngle, m_VertAngle;

	void ProcessMouseMovement(float xoffset, float yoffset);
	void FreeCam(Input &input, float deltatime);
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	void Update(Display &display, Input &input, float deltatime, bool freecam, float fov, float aspect, float zNear, float zFar);
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

	inline void SetPos(glm::vec3 pos)
	{
		m_pos = pos;
	}

	inline void LockCursor()
	{
		m_CursorLocked = true;
	}

	inline void UnlockCursor()
	{
		m_CursorLocked = false;
	}
};

#endif
