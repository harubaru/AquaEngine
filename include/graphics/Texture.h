#ifndef AQUAGL_TEXTURE_H
#define AQUAGL_TEXTURE_H

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <util/stb_image.h>

class Texture {
private:
	GLuint m_texHandle;
public:
	Texture(std::string FilePath);
	Texture(){}
	~Texture();

	void LoadFile(std::string FilePath);

	void Bind(GLuint texUnit);
	void Unbind();
};

#endif
