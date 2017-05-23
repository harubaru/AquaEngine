#ifndef AQUAGL_MESH_H
#define AQUAGL_MESH_H

#include <GL/glew.h>
#include <graphics/glm/glm.hpp>

struct Vertex {
	Vertex(float x, float y, float z) { position = glm::vec3(x, y, z); }
	glm::vec3 position;
};

enum buffer_pos {
	POSITION_POS = 0
};

class Mesh{
private:
	static const unsigned int NUM_BUFFERS = 1;

	GLsizei DrawCount;

	GLuint m_VertexArrayObject;
	GLuint m_VertexArrayBuffers[NUM_BUFFERS];
public:
	Mesh(Vertex* vertices, GLsizei VertexCount);
	~Mesh();

	void Draw();
};

#endif

