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
        int ret = gl3wInit();
	switch (ret) {
	case GL3W_OK:
		break;
	case GL3W_ERROR_INIT:
		/* This usually occurs when GL3W can't detect GL version */
		LOG("GL3W can't detect OpenGL Version\n");
		break;
	case GL3W_ERROR_LIBRARY_OPEN:
		LOG("GL3W can't detect OpenGL Library\n");
		break;
	case GL3W_ERROR_OPENGL_VERSION:
		LOG("OpenGL Version 3.0 or higher is required to run this program\n");
		break;
	default:
		break;
	}

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::Clear(void)
{
	this->Clear(0.0f, 0.0f, 0.0f);
}

void Graphics::Clear(float r, float g, float b)
{
	int w, h;
	m_Display->GetSize(&w, &h);
	glViewport(0, 0, w, h);
	glClearColor(r, g, b, 1.0f);
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

bool GL_IsSupported(std::string extension)
{
	const char *extensions_cstr = (const char *)glGetString(GL_EXTENSIONS);
	
	if (!extensions_cstr)
		return false;
	
	std::string extensions(extensions_cstr);

	// OpenGL is going to complain about us using a deprecated method to get a string of all extensions.
	(void)glGetError();

	if (extensions.find(extension) != std::string::npos)
		return true;

	return false;
}
