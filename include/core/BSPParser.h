#ifndef AQUAENGINE_CORE_BSPPARSER_H
#define AQUAENGINE_CORE_BSPPARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <graphics/glm/glm.hpp>
#include <graphics/Mesh.h>
#include <core/BSPFile.h>
#include <core/Debug.h>

#include <export.h>

class API BSPParser {
private:
	bool processHeader(unsigned char* data, size_t data_len);
	void processLump(unsigned char* data, size_t data_len, unsigned int lump_type, bsp_lump_t* lump);
	void processVertexLump(unsigned char* data, size_t data_len, bsp_lump_t* lump);
	void processEdgeLump(unsigned char* data, size_t data_len, bsp_lump_t* lump);
	void processSurfedgeLump(unsigned char* data, size_t data_len, bsp_lump_t* lump);
	void processFaceLump(unsigned char* data, size_t data_len, bsp_lump_t* lump);

public:
	BSPParser() : success(false) {}
	BSPParser(const std::string &path) { Load(path); }

	void Load(const std::string &path);
	void GetMeshes(void);

	std::vector<glm::vec3> vertices;
	std::vector<bsp_edge_t> map_edges;
	std::vector<bsp_surfedge_t> map_surfedges;
	std::vector<bsp_face_t> map_faces;

	bool success;
};

#endif
