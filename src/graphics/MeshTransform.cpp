#include <graphics/MeshTransform.h>

glm::mat4 MeshTransform::GetModel()
{
	glm::mat4 Model;

	Model = glm::translate(Model, m_Pos);
	Model = glm::rotate(Model, m_Angle, m_Rot);
	Model = glm::scale(Model, m_Scale);

	return Model;
}

