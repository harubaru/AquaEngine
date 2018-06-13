#include <graphics/Texture.h>

Texture::Texture(std::string FilePath, GLenum Target) : mTarget(Target)
{
	LoadFile(FilePath, Target);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTexHandle);
}

void Texture::Bind(GLuint texUnit)
{
	if(texUnit > GL_MAX_TEXTURE_UNITS)
		return;

	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(mTarget, mTexHandle);
}

void Texture::Unbind()
{
	glBindTexture(mTarget, 0);
}

void Texture::LoadFile(std::string FilePath, GLenum Target)
{
	mTarget = Target;
	int w, h, comp;
	unsigned char* texData = stbi_load(FilePath.c_str(), &w, &h, &comp, STBI_rgb_alpha);

	if(texData == NULL) {
		std::cout << "ERROR: Cannot load Texture! FILE: " << FilePath << std::endl;
		return;
	}

	glGenTextures(1, &mTexHandle);
	glBindTexture(mTarget, mTexHandle);

	if(comp == 3) {
		glTexImage2D(mTarget, 0, GL_SRGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	} else if (comp == 4) {
		glTexImage2D(mTarget, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	}

	glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(mTarget);

	glBindTexture(mTarget, 0);

	stbi_image_free(texData);
}
