#include <graphics/TextRenderer.h>

TextRenderer::TextRenderer(int InitialWidth, int InitialHeight)
{
	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// setup quad in graphics card
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// setup shader and shader data
	mTextShader.Load("./resources/shaders/text/vert_text.glsl", "./resources/shaders/text/frag_text.glsl");
	mTextShader.Bind();
	mTextShader.SetMat4("Projection", glm::ortho(0.0f, (float)InitialWidth, 0.0f, (float)InitialHeight));
	mTextShader.SetInt("Text", 0);
	mTextShader.Unbind();
}

void TextRenderer::LoadFont(std::string Path, int Size)
{
	FT_Library ft;
	if(FT_Init_FreeType(&ft))
		std::cout << "FreeType2: Could not initialize FreeType library." << std::endl;

	FT_Face face;
	if(FT_New_Face(ft, Path.c_str(), 0, &face))
		std::cout << "FreeType2: Could not load font: " << Path << std::endl;

	FT_Set_Pixel_Sizes(face, 0, Size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for(unsigned char c = 0; c < 128; c++) {
		if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "FreeType2: Could not load Glyph." << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(unsigned int)face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string Text, float x, float y, float scale, glm::vec3 Color)
{
	mTextShader.Bind();
	mTextShader.SetVec3("TextColor", Color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAO);

	std::string::const_iterator c;
	for(c = Text.begin(); c!= Text.end(); c++) {
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h, 0.0, 0.0 },
			{ xpos,     ypos,     0.0, 1.0},
			{ xpos + w, ypos,     1.0, 1.0 },

			{ xpos,     ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos,     1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mTextShader.Unbind();
}
