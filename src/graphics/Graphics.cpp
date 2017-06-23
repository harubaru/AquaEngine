#include <graphics/Graphics.h>

struct hardwareinfo_t {
	std::string Vendor;
	std::string Renderer;
	std::string Version;
	std::string SL_Version;
};

Graphics::Graphics(Display& display)
{
	m_Display = &display;

	// Initializing GLEW
	glewExperimental = true;
	GLenum code = glewInit();
	if(code != GLEW_OK)
		std::cout << "GLEW Error: " << glewGetErrorString(code) << std::endl;

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
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

hardwareinfo_t Graphics::GetHardwareInfo()
{
	hardwareinfo_t ret = {
		.Vendor = std::string((const char*)glGetString(GL_VENDOR)),
		.Renderer = std::string((const char*)glGetString(GL_RENDERER)),
		.Version = std::string((const char*)glGetString(GL_VERSION)),
		.SL_Version = std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION))
	};

	return ret;
}
