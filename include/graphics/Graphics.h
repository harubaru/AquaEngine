#ifndef AQUA2D_GRAPHICS_H
#define AQUA2D_GRAPHICS_H

#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <graphics/Display.h>

class Graphics
{
private:
	Display* m_Display;
public:
	Graphics(Display& display);
	
	void InitWindow(const char* title, int w, int h, uint32_t sdl_flags);
	void Clear(float, float, float);
};

#endif
