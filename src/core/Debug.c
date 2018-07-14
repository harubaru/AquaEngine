#include <core/Debug.h>

static FILE *debug_file;
static clock_t init_time;
static unsigned int  enabled = 0;

void Debug_Init(const char *fp)
{
	init_time = clock();
	debug_file = fopen(fp, "w");
	enabled = 1;
}

void Debug_printf(const char *file, unsigned line, const char *s, ...)
{
	if (!enabled)
		return;
	
	clock_t diff_time = clock();
	float res = -1 * ((double)(init_time - diff_time) / CLOCKS_PER_SEC);

	fprintf(debug_file, "[%f] ", res);
	if (file && line)
		fprintf(debug_file, "%s @ %u: ", file, line);

	va_list args;
	va_start(args, s);
	vfprintf(debug_file, s, args);
	va_end(args);

	fflush(debug_file);
}

void Debug_AssertGL(const char *file, unsigned line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		switch (err) {
		case GL_INVALID_OPERATION:
			Debug_printf(file, line, "OpenGL Error: GL_INVALID_OPERATION\n");
			break;
		case GL_INVALID_ENUM:
			Debug_printf(file, line, "OpenGL Error: GL_INVALID_ENUM\n");
			break;
		case GL_INVALID_VALUE:
			Debug_printf(file, line, "OpenGL Error: GL_INVALID_VALUE\n");
			break;
		case GL_OUT_OF_MEMORY:
			Debug_printf(file, line, "OpenGL Error: GL_OUT_OF_MEMORY\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			Debug_printf(file, line, "OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION\n");
			break;
		}
	}
}

void Debug_FatalError()
{
	Debug_Kill();
	exit(EXIT_FAILURE);
}

void Debug_Kill(void)
{
	fclose(debug_file);
}
