#include <core/SceneObject.h>

SceneObject::SceneObject(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale)
{
	Load(ModelPath, TexturePath, Position, RotAxis, Scale);
}

void SceneObject::Load(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale)
{
	mModel.Load(ModelPath);
	mTexture = Texture_Load(TexturePath.c_str());
	Transform.Load(Position, RotAxis, Scale);
}

void SceneObject::Destroy()
{
	mModel.Destroy();
	Transform.Destroy();
	Texture_Destroy(mTexture);
}

void SceneObject::Render(Shader& shader)
{
	shader.SetModel(Transform.GetModel());
	Texture_Bind(mTexture, 0);
	ShadowMapping_Bind();
	mModel.Render();
	ShadowMapping_Unbind();
	Texture_Bind(0, 0);
}

bool SceneObject::operator==(SceneObject &object)
{
	if (this == &object)
		return true;
	else
		return false;
}
