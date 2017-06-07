#include <graphics/Graphics.h>

Graphics::Graphics(Display& display)
{
	m_Display = &display;

	// Initializing GLEW
	glewExperimental = true;
	GLenum code = glewInit();
	if(code != GLEW_OK)
		std::cout << "Error initializing GLEW: " << glewGetErrorString(code) << std::endl;

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::Clear(float r, float g, float b)
{
	int w, h;
	m_Display->GetSize(&w, &h);
	glViewport(0, 0, w, h);
	glClearColor(r, g, b, 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::GetGLError()
{
	uint32_t ErrorCode = glGetError();
	if(ErrorCode != GL_NO_ERROR) {
		std::string ErrorStr;
		switch(ErrorCode) {
			case GL_INVALID_ENUM: ErrorStr = "OpenGL Error: INVALID_ENUM"; break;
			case GL_INVALID_VALUE: ErrorStr = "OpenGL Error: INVALID_VALUE"; break;
			case GL_INVALID_OPERATION: ErrorStr = "OpenGL Error: INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW: ErrorStr = "OpenGL Error: STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW: ErrorStr = "OpenGL Error: STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY: ErrorStr = "OpenGL Error: OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: ErrorStr = "OpenGL Error: INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << ErrorStr << std::endl; // print formatted error
	}
}
