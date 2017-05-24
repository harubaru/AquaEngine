#ifndef AQUAGL_RENDERER_H
#define AQUAGL_RENDERER_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

/*  Handles Input
 */

class Display
{
	SDL_Window* m_Window;
	SDL_GLContext m_OpenGLContext;
	SDL_Event m_InputEvent;
public:
	Display(int w, int h, const std::string& title);
	~Display();
	
	bool Close;

	void Update();
	void GetSize(int* w, int* h);

	SDL_Window* GetWindow();
};

#endif

