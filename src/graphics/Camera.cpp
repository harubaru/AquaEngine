#include <graphics/Camera.h>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
        m_Projection = glm::perspective(fov, aspect, zNear, zFar);
        m_pos = pos;
        m_forward = glm::vec3(0, 0, -1);
        m_up = glm::vec3(0, 1, 0);
        m_CursorLocked = false;
        m_MouseSensitivity = 2;
        m_HorizAngle = 0.f;
}

void Camera::Update(Display &display, Input &input, float deltatime, bool freecam, float fov, float aspect, float zNear, float zFar)
{

	if (!input.FocusLossed())
		UnlockCursor();
	else
		LockCursor();

        if (m_CursorLocked) {
                int w, h, yaw, pitch;
                display.GetSize(&w, &h);

		SDL_GetMouseState(&yaw, &pitch);
		yaw -= (w / 2);
		pitch -= (h / 2);

		if (!(yaw == 0 && pitch == 0)) {
			SDL_SetWindowGrab(display.GetWindow(), SDL_TRUE);
			SDL_WarpMouseInWindow(display.GetWindow(), w / 2, h / 2);
//			SDL_SetRelativeMouseMode(SDL_TRUE);
        		SDL_ShowCursor(SDL_DISABLE);
			float xoffset = yaw;
			float yoffset = 0 - pitch;

			ProcessMouseMovement(xoffset * deltatime, yoffset * deltatime);
		}

		if (freecam)
			this->FreeCam(input, deltatime);
        } else {
		SDL_SetWindowGrab(display.GetWindow(), SDL_FALSE);
	}

        m_Projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_HorizAngle += xoffset;
	m_VertAngle += yoffset;

	if (m_VertAngle > 89.0f)
		m_VertAngle = 89.0f;
	if (m_VertAngle < -89.0f)
		m_VertAngle = -89.0f;

	this->SetView(m_HorizAngle, m_VertAngle);
}

void Camera::FreeCam(Input &input, float deltatime)
{
	float velocity = 16 * deltatime;
	if (input.GetKeyState(SDL_SCANCODE_W))
		m_pos += m_forward * velocity;
	if (input.GetKeyState(SDL_SCANCODE_S))
		m_pos -= m_forward * velocity;
	if (input.GetKeyState(SDL_SCANCODE_A))
		m_pos -= m_right * velocity;
	if (input.GetKeyState(SDL_SCANCODE_D))
		m_pos += m_right * velocity;
}

void Camera::SetView(float yaw, float pitch)
{
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_forward = glm::normalize(direction);

	m_right = glm::normalize(glm::cross(m_forward, m_up));
}
