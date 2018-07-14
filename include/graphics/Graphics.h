#ifndef AQUAENGINE_GRAPHICS_GRAPHICS_H
#define AQUAENGINE_GRAPHICS_GRAPHICS_H

#include <export.h>

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <core/ConVar.h>

#include <graphics/Display.h>
#include <graphics/Shader.h>
#include <graphics/gl3w.h>

#include <core/ConVar.h>

struct API hardwareinfo_t;

class API Graphics
{
private:
	Display* m_Display;
public:
	Graphics(Display& display);

	void InitWindow(const char* title, int w, int h, uint32_t sdl_flags);
	void Clear(void);
	void Clear(float, float, float);
	void GetGLError();
	hardwareinfo_t GetHardwareInfo();
};

API bool GL_IsSupported(std::string extension);

#endif
