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

	shader.SetInt("diffuseTexture", 0); // tex 1
	shader.SetInt("shadowMap", 1); // tex 1

	mTexture.Bind(0);
	ShadowMapping_Bind();
	mModel.Render();
	ShadowMapping_Unbind();
	mTexture.Unbind();

	if(shader.BindState)
		shader.Unbind();
}

bool PhysEntity::operator==(PhysEntity &ent)
{
	if (this == &ent)
		return true;
	else
		return false;
}
