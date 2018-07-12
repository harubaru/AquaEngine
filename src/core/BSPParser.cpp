#include <core/BSPParser.h>

void BSPParser::Load(const std::string &path)
{
	std::ifstream file(path, std::ios::in | std::ios::ate | std::ios::binary);
	unsigned char* data;
	size_t data_len;

	/* Get file size */
	file.seekg(0, file.end);
	data_len = file.tellg();
	file.seekg(0, file.beg);

	/* Read file into a buffer */
	data = new unsigned char[data_len];
	file.read((char*)data, data_len);
	file.close();

	bool success = true;
	if (!processHeader(data, data_len))
		success = false;

	delete data;
}

bool BSPParser::processHeader(unsigned char* data, size_t data_len) {
	bsp_header_t* header;

	if (sizeof(*header) > data_len) {
		LOG("Invalid BSP file\n");
		return false;
	}

	/* Set header struct to point to its location in the file */
	header = (bsp_header_t*)(data);

	if (header->file_identifier != BSP_FILE_IDENTIFIER) {
		LOG("Invalid BSP file identifier.\n"); 
		return false;
	}
	if (header->version < 17 || header->version > 29) { 
		LOG("Invalid BSP file version.\n");
		return false;
	}

	for (int i=0; i < BSP_TOTAL_LUMPS; i++)
		processLump(data, data_len, i, &header->lumps[i]);

	return true;
}

void BSPParser::processLump(unsigned char* data, size_t data_len, uint32_t lump_type, bsp_lump_t* lump) {
	/* Make sure the location the lump indicates data is in is inside the file */
	if (lump->file_offset >= data_len) {
		LOG("Not enough data in buffer to hold header\n");
	}

	switch(lump_type) {
	case LUMP_VERTEXES:
		processVertexLump(data, data_len, lump);
		break;
	case LUMP_EDGES:
		processEdgeLump(data, data_len, lump);
		break;
	case LUMP_SURFEDGES:
		processSurfedgeLump(data, data_len, lump);
		break;
	case LUMP_FACES:
		processFaceLump(data, data_len, lump);
		break;
	case LUMP_ENTITIES:
	case LUMP_PLANES:
	case LUMP_TEXDATA:
	case LUMP_VISIBILITY:
	case LUMP_NODES:
	case LUMP_TEXINFO:
	case LUMP_LIGHTING:
	case LUMP_OCCLUSION:
	case LUMP_LEAFS:
	case LUMP_FACEIDS:
	case LUMP_MODELS:
	case LUMP_WORLDLIGHTS:
	case LUMP_LEAFFACES:
	case LUMP_LEAFBRUSHES:
	case LUMP_BRUSHES:
	case LUMP_BRUSHSIDES:
	case LUMP_AREAS:
	case LUMP_AREAPORTALS:
	//case LUMP_PORTALS:
	//case LUMP_UNUSED0:
	case LUMP_PROPCOLLISION:
	//case LUMP_CLUSTERS:
	//case LUMP_UNUSED1:
	case LUMP_PROPHULLS:
	//case LUMP_PORTALVERTS:
	//case LUMP_UNUSED2:
	case LUMP_PROPHULLVERTS:
	//case LUMP_CLUSTERPORTALS:
	//case LUMP_UNUSED3:
	case LUMP_PROPTRIS:
	case LUMP_DISPINFO:
	case LUMP_ORIGINALFACES:
	case LUMP_PHYSDISP:
	case LUMP_PHYSCOLLIDE:
	case LUMP_VERTNORMALS:
	case LUMP_VERTNORMALINDICES:
	case LUMP_DISP_LIGHTMAP_ALPHAS:
	case LUMP_DISP_VERTS:
	case LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS:
	case LUMP_GAME_LUMP:
	case LUMP_LEAFWATERDATA:
	case LUMP_PRIMITIVES:
	case LUMP_PRIMVERTS:
	case LUMP_PRIMINDICES:
	case LUMP_PAKFILE:
	case LUMP_CLIPPORTALVERTS:
	case LUMP_CUBEMAPS:
	case LUMP_TEXDATA_STRING_DATA:
	case LUMP_TEXDATA_STRING_TABLE:
	case LUMP_OVERLAYS:
	case LUMP_LEAFMINDISTTOWATER:
	case LUMP_FACE_MACRO_TEXTURE_INFO:
	case LUMP_DISP_TRIS:
	case LUMP_PHYSCOLLIDESURFACE:
	//case LUMP_PROP_BLOB:
	case LUMP_WATEROVERLAYS:
	case LUMP_LIGHTMAPPAGES:
	case LUMP_LEAF_AMBIENT_INDEX_HDR:
	case LUMP_LIGHTMAPPAGEINFOS:
	case LUMP_LEAF_AMBIENT_INDEX:
	case LUMP_LIGHTING_HDR:
	case LUMP_WORLDLIGHTS_HDR:
	case LUMP_LEAF_AMBIENT_LIGHTING_HDR:
	case LUMP_LEAF_AMBIENT_LIGHTING:
	case LUMP_XZIPPAKFILE:
	case LUMP_FACES_HDR:
	case LUMP_MAP_FLAGS:
	case LUMP_OVERLAY_FADES:
	case LUMP_DISP_MULTIBLEND:
	break;
	default:
		LOG("Encountered unknown lump type.\n");
	}
}

void BSPParser::processVertexLump(unsigned char* data, size_t data_len, bsp_lump_t* lump) {
	bsp_vertex_t* verts;
	size_t number_verts;

	if (data_len < lump->file_offset + lump->size)
		LOG("Vertex lump doesn't seem to fit in the data buffer?\n");

	if ((lump->size % sizeof(*verts)) != 0)
		LOG("Vertex lumps are uneven\n");

	verts = (bsp_vertex_t*)(data + lump->file_offset);
	number_verts = lump->size / sizeof(*verts);

	for (size_t i = 0; i < number_verts; i++)
		vertices.push_back({ verts[i].x, verts[i].y, verts[i].z });
}

void BSPParser::processEdgeLump(unsigned char* data, size_t data_len, bsp_lump_t* lump) {
	bsp_edge_t* edges;
	size_t number_edges;

	if (data_len < lump->file_offset + lump->size)
		LOG("Edge lump doesn't seem to fit in the data buffer?\n");

	if ((lump->size % sizeof(*edges)) != 0)
		LOG("Edge lumps are uneven\n");

	edges = (bsp_edge_t*)(data + lump->file_offset);
	number_edges = lump->size / sizeof(*edges);


	for (size_t i = 0; i < number_edges; i++)
		map_edges.push_back(edges[i]);
}

void BSPParser::processSurfedgeLump(unsigned char* data, size_t data_len, bsp_lump_t* lump) {
	bsp_surfedge_t* surfedges;
	size_t number_surfedges;

	if (data_len < lump->file_offset + lump->size)
		LOG("Surfedge lump doesn't seem to fit in the data buffer?\n");

	if ((lump->size % sizeof(*surfedges)) != 0)
		LOG("Surfedge lumps are uneven\n");

	surfedges = (bsp_surfedge_t*)(data + lump->file_offset);
	number_surfedges = lump->size / sizeof(*surfedges);


	for (size_t i = 0; i < number_surfedges; i++) {
		map_surfedges.push_back(surfedges[i]);
	}
}

void BSPParser::processFaceLump(unsigned char* data, size_t data_len, bsp_lump_t* lump) {
	bsp_face_t* faces;
	size_t number_faces;

	if (data_len < lump->file_offset + lump->size)
		LOG("Face lump doesn't seem to fit in the data buffer?\n");

	if ((lump->size % sizeof(*faces)) != 0)
		LOG("Face lumps are uneven\n");

	faces = (bsp_face_t*)(data + lump->file_offset);
	number_faces = lump->size / sizeof(*faces);


	for (size_t i = 0; i < number_faces; i++) {
		map_faces.push_back(faces[i]);
	}
}
