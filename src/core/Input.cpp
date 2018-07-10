#include <core/Input.h>

void Input::Load()
{
	m_WindowClose = false;
	for(unsigned i = 0; i < SDL_NUM_SCANCODES; i++)
		m_KeyStates[i] = false;

	for(unsigned i = 0; i < 5; i++)
		m_MouseStates[i] = false;
}

void Input::Update()
{
	while(SDL_PollEvent(&m_InputEvent)) {
		// Key input done in core/Input

		switch(m_InputEvent.type) {
		case SDL_QUIT:
			m_WindowClose = true;
			break;

		// keyboard input
		case SDL_KEYDOWN:
			m_KeyStates[m_InputEvent.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			m_KeyStates[m_InputEvent.key.keysym.scancode] = false;
			break;
			
			case SDL_WINDOWEVENT:
				if (m_InputEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
					m_Focus = false;
				else if (m_InputEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
					m_Focus = true;
			break;

		// mouse input
		case SDL_MOUSEMOTION:
			m_MouseX = m_InputEvent.motion.x;
			m_MouseY = m_InputEvent.motion.x;
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_MouseStates[m_InputEvent.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			m_MouseStates[m_InputEvent.button.button] = false;
			break;

		// TODO: Support Mousewheel
		}
	}
}

bool Input::GetKeyState(int keycode)
{
	if(keycode <= SDL_NUM_SCANCODES)
		return m_KeyStates[keycode];
	else return false;
}

bool Input::GetButtonState(int button)
{
	if(button <= 5)
		return m_MouseStates[button];
	else return false;
}

bool Input::FocusLossed()
{
		return m_Focus;
}

int Input::GetMouseX()
{
	return m_MouseX;
}

int Input::GetMouseY()
{
	return m_MouseY;
}