#ifndef AQUAENGINE_CORE_INPUT_H
#define AQUAENGINE_CORE_INPUT_H

#include <SDL2/SDL.h>

class Input {
private:
	SDL_Event m_InputEvent;
public:
	Input() : m_WindowClose(false) {}
	void Update();

	bool m_WindowClose;
};

#endif
