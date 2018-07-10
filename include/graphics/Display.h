#ifndef AQUAENGINE_GRAPHICS_DISPLAY_H
#define AQUAENGINE_GRAPHICS_DISPLAY_H

#include <export.h>

#include <string>

#include <SDL2/SDL.h>
#include <core/Input.h>
#include <core/ConVar.h>
#include <util/stb_image.h>
#include <core/Debug.h>

#ifdef main
#undef main
#endif

class API Display
{
	SDL_Window* m_Window;
	SDL_GLContext m_OpenGLContext;
public:
	Display(int w, int h, const std::string& title, uint32_t AdditionalFlags);
	~Display();

	bool Close;

	void DestroyWindow();
	void Update();
	void LimitRefreshRate(double *deltatime);
	void GetSize(int* w, int* h);

	SDL_Window* GetWindow();
	Input m_Input;
};

#endif
