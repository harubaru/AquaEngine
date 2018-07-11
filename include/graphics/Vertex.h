#ifndef AQUAENGINE_GRAPHICS_VERTEX_H
#define AQUAENGINE_GRAPHICS_VERTEX_H

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

#endif
