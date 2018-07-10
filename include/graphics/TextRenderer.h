#ifndef AQUAENGINE_GRAPHICS_TEXTRENDERER_H
#define AQUAENGINE_GRAPHICS_TEXTRENDERER_H

#include <export.h>

#include <iostream>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <graphics/Shader.h>

struct API Character {
	unsigned int TextureID;
	glm::ivec2   Size;
	glm::ivec2   Bearing;
	unsigned int Advance;
};

class API TextRenderer {
private:
	unsigned int mVAO, mVBO;
	Shader       mTextShader;
	std::map<char, Character> Characters;
public:
	TextRenderer(int InitialWidth, int InitialHeight);

	void LoadFont(std::string Path, int Size);
	void RenderText(std::string Text, float x, float y, float scale, glm::vec3 Color);
};

#endif
