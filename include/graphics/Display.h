#ifndef AQUAENGINE_GRAPHICS_DISPLAY_H
#define AQUAENGINE_GRAPHICS_DISPLAY_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Display
{
	SDL_Window* m_Window;
	SDL_GLContext m_OpenGLContext;
	SDL_Event m_InputEvent;
public:
	Display(int w, int h, const std::string& title, uint32_t AdditionalFlags);
	~Display();

	bool Close;

	void DestroyWindow();
	void Update();
	void GetSize(int* w, int* h);

	SDL_Window* GetWindow();
};

#endif
