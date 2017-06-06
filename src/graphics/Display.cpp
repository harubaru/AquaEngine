#include <graphics/Display.h>

Display::Display(int w, int h, const std::string& title, uint32_t AdditionalFlags) : Close(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	uint32_t SDL_Window_Flags = SDL_WINDOW_OPENGL;
	if(AdditionalFlags)
		SDL_Window_Flags |= AdditionalFlags;

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_Window_Flags);
	m_OpenGLContext = SDL_GL_CreateContext(m_Window);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_OpenGLContext);
	SDL_DestroyWindow(m_Window);
}

void Display::Update()
{
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SwapWindow(m_Window);

	while(SDL_PollEvent(&m_InputEvent)) {
		//TODO: Key Input Too!
		if(m_InputEvent.type == SDL_QUIT)
			Close = true;
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
