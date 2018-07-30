#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Display.h>

Display::Display(int w, int h, const std::string& title, uint32_t AdditionalFlags) : Close(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ConVar_GetFloat("r_glmajor"));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ConVar_GetFloat("r_glminor"));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	uint32_t SDL_Window_Flags = SDL_WINDOW_OPENGL;
	if (AdditionalFlags)
		SDL_Window_Flags |= AdditionalFlags;

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_Window_Flags);
	m_OpenGLContext = SDL_GL_CreateContext(m_Window);
	m_Input.Load();
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_OpenGLContext);
	SDL_DestroyWindow(m_Window);
}

void Display::DestroyWindow()
{
	SDL_DestroyWindow(m_Window);
}

void Display::Update()
{
	int vsync = (int)ConVar_GetFloat("r_vsync");
	if (vsync == 1 || vsync == -1) {
		if (SDL_GL_SetSwapInterval(vsync) == -1) {
			LOG("vsync is not supported!");
			ConVar_SetFloat("r_vsync", 0);
		}
	}
	
	SDL_GL_SwapWindow(m_Window);
	m_Input.Update();
}

void Display::LimitRefreshRate(double *deltatime)
{
	float maxfps = ConVar_GetFloat("r_maxfps");
	double deltatime_ms = *deltatime * 1000.0; // convert to milliseconds because SDL_Delay only takes in milliseconds
	if (deltatime_ms < 1000 / maxfps) { // check if current fps is over maxfps, if so then wait out the rest of the frame
		SDL_Delay((1000 / maxfps) - deltatime_ms);
		*deltatime = static_cast<double>(1.0 / maxfps); // set deltatime to the real fps and maxfps into seconds instead of hertz
	}
}

void Display::GetSize(int* w, int* h)
{
	SDL_GetWindowSize(m_Window, w, h);
}

SDL_Window* Display::GetWindow()
{
	return m_Window;
}
