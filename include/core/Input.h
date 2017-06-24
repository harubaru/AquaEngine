#ifndef AQUAENGINE_CORE_INPUT_H
#define AQUAENGINE_CORE_INPUT_H

#include <SDL2/SDL.h>

class Input {
private:
	SDL_Event m_InputEvent;
	bool m_KeyStates[SDL_NUM_SCANCODES];
	bool m_MouseStates[5];
	int m_MouseX, m_MouseY;
public:
	Input();
	void Update();

	bool GetKeyState(int key);
	bool GetButtonState(int button);
	int GetMouseX();
	int GetMouseY();

	bool m_WindowClose;
};

#endif
