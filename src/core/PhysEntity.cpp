#include <core/PhysEntity.h>

PhysEntity::PhysEntity(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale)
{
	Load(ModelPath, TexturePath, Position, RotAxis, Scale);
}

void PhysEntity::Load(const std::string& ModelPath, const std::string& TexturePath, vec3 Position, vec3 RotAxis, vec3 Scale)
{
	mModel.Load(ModelPath);
	mTexture.LoadFile(TexturePath, GL_TEXTURE_2D);
	Transform.Load(Position, RotAxis, Scale);
}

void PhysEntity::Render(Shader& shader)
{
	if(!shader.BindState)
		shader.Bind();

	shader.SetModel(Transform.GetModel());

	mTexture.Bind(0);
	mModel.Render();
	mTexture.Unbind();

	if(shader.BindState)
		shader.Unbind();
}
