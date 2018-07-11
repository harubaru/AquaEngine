#ifndef AQUAENGINE_GRAPHICS_MAP_H
#define AQUAENGINE_GRAPHICS_MAP_H

#include <export.h>

#include <graphics/glm/gtx/transform.hpp>
#include <graphics/glm/glm.hpp>
#include <graphics/Vertex.h>
#include <graphics/Shader.h>
#include <core/BSPParser.h>

class API MapFace {
private:
	GLsizei DrawCount;
	GLuint m_VertexArrayObject;
	GLuint m_ElementBufferObject;
public:
	MapFace(std::vector<GLuint> indices);

	void Load(std::vector<GLuint> indices);

	void Destroy();
	void Draw();
};

class API Map {
private:
	GLuint m_VertexArrayBuffer;
	std::vector<MapFace> mapfaces;
public:
	Map() {}
	Map(BSPParser *parser);

	void Load(BSPParser *parser);
	void Destroy();
	void Render(Shader &shader);
};

#endif
