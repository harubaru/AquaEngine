#include <core/Input.h>

void Input::Update()
{
	while(SDL_PollEvent(&m_InputEvent)) {
		// Key input done in core/Input
		if(m_InputEvent.type == SDL_QUIT)
			m_WindowClose = true;
	}
}
