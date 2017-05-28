#ifndef AQUAGL_OBJ_H
#define AQUAGL_OBJ_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <graphics/glm/glm.hpp>

bool ParseOBJFile(const std::string& FilePath, std::vector<glm::vec3>& processed_vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords, std::vector<unsigned int> vertexindices);

#endif

