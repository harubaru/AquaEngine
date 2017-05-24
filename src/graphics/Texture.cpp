#include <graphics/Texture.h>

Texture::Texture(std::string& FilePath)
{
	int w, h, comp;
	unsigned char* texData = stbi_load(FilePath.c_str(), &w, &h, &comp, STBI_rgb_alpha);
	
	if(texData == NULL) {
		std::cout << "ERROR: Cannot load Texture! FILE: " << FilePath << std::endl;
		return;
	}

	glGenTextures(1, &m_texHandle);
	glBindTexture(GL_TEXTURE_2D, m_texHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::Bind(GLuint texUnit)
{
	if(texUnit < GL_MAX_TEXTURE_UNITS)
		return;

	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, m_texHandle);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

