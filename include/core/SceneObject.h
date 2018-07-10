#ifndef AQUAENGINE_CORE_SCENE_OBJECT_H
#define AQUAENGINE_CORE_SCENE_OBJECT_H

#include <export.h>

#include <graphics/Model.h>
#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/MeshTransform.h>
#include <graphics/ShadowMapping.h>

class API SceneObject {
private:
	Model mModel;
	GLuint mTexture;
public:
	SceneObject() {}
	SceneObject(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale);

	void Load(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale);
	void Destroy();
	void Render(Shader& shader);

	bool operator==(SceneObject &ent);

	MeshTransform Transform;
};

#endif
