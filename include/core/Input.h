#ifndef AQUAENGINE_CORE_INPUT_H
#define AQUAENGINE_CORE_INPUT_H

#include <export.h>

#include <SDL2/SDL.h>

class API Input {
private:
	SDL_Event m_InputEvent;
	bool m_KeyStates[SDL_NUM_SCANCODES];
	bool m_MouseStates[5];
	bool m_Focus;
	int m_MouseX, m_MouseY;
public:
	Input() {}
	void Load();
	void Update();

	bool GetKeyState(int key);
	bool GetButtonState(int button);
	bool FocusLossed();
	int GetMouseX();
	int GetMouseY();

	bool m_WindowClose;
};

#endif
