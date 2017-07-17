#ifndef AQUAENGINE_GRAPHICS_TEXTURE_H
#define AQUAENGINE_GRAPHICS_TEXTURE_H

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <util/stb_image.h>

class Texture {
private:
	GLuint mTexHandle;
	GLenum mTarget;
public:
	Texture(std::string FilePath, GLenum Target);
	Texture(){}
	~Texture();

	void LoadFile(std::string FilePath, GLenum Target);

	void Bind(GLuint texUnit);
	void Unbind();

	inline GLuint GetTexHandle() { return mTexHandle; }
};

#endif
