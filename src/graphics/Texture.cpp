#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Texture.h>

GLuint Texture_Load(const char *f)
{
	GLuint tex = 0;
	GLenum iformat = 0, format = 0;
	int width, height, components;
	unsigned char *data = stbi_load(f, &width, &height, &components, 0);

	// if data is null, stbi_load didn't find the file.
	if (!data)
		return 0;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	if (components == 3) {
		iformat = GL_SRGB;
		format = GL_RGB;
	} else if (components == 4) {
		iformat = GL_SRGB_ALPHA;
		format = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data); /* free image data once we sent the data to the GPU */

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

	/*
	
	Nearest-Neighbor Filtering:
	GL_TEXTURE_MIN_FILTER - GL_NEAREST
	GL_TEXTURE_MAG_FILTER - GL_NEAREST

	Nearest-Neighbor Mipmap Filtering:
	GL_TEXTURE_MIN_FILTER - GL_NEAREST_MIPMAP_NEAREST
	GL_TEXTURE_MAG_FILTER - GL_NEAREST

	Bilinear Filtering:
	GL_TEXTURE_MIN_FILTER - GL_LINEAR
	GL_TEXTURE_MAG_FILTER - GL_LINEAR

	Trilinear Filtering
	GL_TEXTURE_MIN_FILTER - GL_LINEAR_MIPMAP_LINEAR
	GL_TEXTURE_MAG_FILTER - GL_LINEAR

	*/
	if (ConVar_GetFloat("mat_filtertextures")) {
		if (ConVar_GetFloat("mat_mipmaptextures")) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		if (ConVar_GetFloat("mat_mipmaptextures")) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if (ConVar_GetFloat("mat_aniso")) {
		if (GL_IsSupported("GL_EXT_texture_filter_anisotropic")) {
			GLfloat aniso_level = ConVar_GetFloat("mat_aniso");
			GLfloat aniso_max;

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &aniso_max);

			if (aniso_level > aniso_max) {
				aniso_level = aniso_max;
				ConVar_SetFloat("mat_aniso", aniso_level);
			}

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, aniso_level);
		} else {
			std::cout << "Texture: Anisotropic Filtering is not supported by your graphics drivers!\n";
			ConVar_SetFloat("mat_aniso", 0.0f);
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

void Texture_Bind(GLuint texid, GLuint texunit)
{
	glActiveTexture(GL_TEXTURE0 + texunit);
	glBindTexture(GL_TEXTURE_2D, texid);
}

void Texture_Destroy(GLuint texid)
{
	glDeleteTextures(1, &texid);
}

void Texture_Cubemap_Bind(GLuint texid)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texid);
}
