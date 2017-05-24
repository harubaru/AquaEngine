#ifndef AQUAGL_MESH_H
#define AQUAGL_MESH_H

#include <GL/glew.h>
#include <graphics/glm/glm.hpp>

struct Vertex {
	Vertex() : position(glm::vec3(0, 0, 0)), texcoord(glm::vec2(0, 0)) {}
	Vertex(float x, float y, float z, float u, float v) { 
		position = glm::vec3(x, y, z);
		texcoord = glm::vec2(u, v);
	}

	glm::vec3 position;
	glm::vec2 texcoord;
};

class Mesh{
private:
	static const unsigned int NUM_BUFFERS = 2;

	GLsizei DrawCount;

	GLuint m_VertexArrayObject;
	GLuint m_VertexArrayBuffer;
public:
	Mesh(Vertex* vertices, GLsizei VertexCount);
	~Mesh();

	void Draw();
};

#endif

