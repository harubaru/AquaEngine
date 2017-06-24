#ifndef AQUAENGINE_GRAPHICS_GRAPHICS_H
#define AQUAENGINE_GRAPHICS_GRAPHICS_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <graphics/Display.h>
#include <graphics/Shader.h>

struct hardwareinfo_t;

class Graphics
{
private:
	Display* m_Display;
public:
	Graphics(Display& display);

	void InitWindow(const char* title, int w, int h, uint32_t sdl_flags);
	void Clear(float, float, float);
	void GetGLError();
	hardwareinfo_t GetHardwareInfo();
};

#endif
