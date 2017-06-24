#ifndef AQUAENGINE_GRAPHICS_MESH_H
#define AQUAENGINE_GRAPHICS_MESH_H

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <graphics/glm/glm.hpp>

struct Vertex {
	Vertex() : position(glm::vec3(0, 0, 0)), normal(glm::vec3(0, 0, 0)), texcoord(glm::vec2(0, 0)) {}
	Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
		position = glm::vec3(x, y, z);
		normal = glm::vec3(nx, ny, nz);
		texcoord = glm::vec2(u, v);
	}

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

class Mesh{
private:
	GLsizei DrawCount;

	GLuint m_IndexBufferObject;
	GLuint m_VertexArrayObject;
	GLuint m_VertexArrayBuffer;
public:
	Mesh(Vertex* vertices, const std::vector<uint32_t>& Indices);
	Mesh(Vertex* vertices, const std::vector<uint32_t>& Indices, size_t drawcount);
	Mesh();

	void Load(Vertex* vertices, const std::vector<uint32_t>& Indices);
	void Load(Vertex* vertices, const std::vector<uint32_t>& Indices, size_t drawcount);

	void Destroy();
	void Draw();
};

#endif
