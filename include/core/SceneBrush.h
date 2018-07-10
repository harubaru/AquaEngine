#ifndef AQUAENGINE_CORE_SCENEBRUSH_H
#define AQUAENGINE_CORE_SCENEBRUSH_H

#include <export.h>

#include <graphics/Mesh.h>
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/MeshTransform.h>
#include <graphics/ShadowMapping.h>

#include <core/SceneObject.h>

class API SceneBrush {
private:
	Mesh mMesh;
	GLuint *mTexture;

	void GenPlane(float width, float height, float texture_size);
public:
	SceneBrush() {}
	SceneBrush(float width, float height, float texture_size, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale);

	void Load(float width, float height, float texture_size, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale);
	void Destroy();
	void Render(Shader& shader);

	bool operator==(SceneBrush &ent);

	MeshTransform Transform;
};

#endif
