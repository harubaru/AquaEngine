#ifndef AQUAENGINE_GRAPHICS_MODEL_H
#define AQUAENGINE_GRAPHICS_MODEL_H

#include <export.h>

#include <iostream>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <graphics/Mesh.h>
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/MeshTransform.h>

class API Model {
private:
	std::vector<Mesh> Meshes;

	void ProcessNode(aiNode* Node, const aiScene* Scene);
	Mesh ProcessMesh(aiMesh* mesh);

	bool MeshFail;
public:
	Model() {}
	Model(const std::string& FilePath);

	void Load(const std::string& FilePath);
	void Destroy();
	void Render();

	MeshTransform Transform;

	std::string FilePath;
	uint32_t MeshCount;
};

#endif
