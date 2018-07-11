#ifndef AQUAENGINE_GRAPHICS_MESH_H
#define AQUAENGINE_GRAPHICS_MESH_H

#include <export.h>

#include <iostream>
#include <string>
#include <vector>
#include <graphics/gl3w.h>
#include <graphics/glm/glm.hpp>
#include <graphics/Vertex.h>

class API Mesh {
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
