#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <graphics/TextureManager.h>

struct TextureEntry {
	std::string Name;
	GLuint tex;
};

std::vector<TextureEntry> TextureTable;

void TextureManager_Parse(const std::string filepath)
{
	std::ifstream file(filepath);

	if (!file.is_open()) {
		Debug_printf(__FILE__, __LINE__, "TextureManager: Can't open file - %s\n", filepath.c_str());
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		TextureEntry entry;
		std::string tex_filepath;

		if ((line == "") || (line.front() == '#')) continue;

		if (!(iss >> entry.Name >> tex_filepath)) {
			Debug_printf(__FILE__, __LINE__, "TextureManager: Invalid Texture: %s\n", line.c_str());
			continue;
		}

		entry.tex = Texture_Load(tex_filepath.c_str());
	
		if (!entry.tex) {
			Debug_printf(__FILE__, __LINE__, "TextureManager: Missing Texture: %s\n", tex_filepath.c_str());
			entry.tex = Texture_Load("./resources/textures/missingtexture.png");
		}

		TextureTable.push_back(entry);
	}
}

GLuint TextureManager_GetTexture(const std::string texturename)
{
	for (auto &i : TextureTable) {
		if (i.Name == texturename)
			return i.tex;
	}

	Debug_printf(__FILE__, __LINE__, "TextureManager: Can't find texture: %s\n", texturename.c_str());

	return TextureManager_GetTexture("missingtexture");
}

void TextureManager_Destroy(void)
{
	for (auto &i : TextureTable) {
		if (i.tex) {
			Texture_Destroy(i.tex);
		} else {
			Debug_printf(__FILE__, __LINE__, "TextureManager: Texture isn't in the GPU's memory for some reason: %s\n", i.Name.c_str());
		}
	}

	TextureTable.clear();
}
