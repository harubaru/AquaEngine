#include <graphics/MeshTransform.h>

void MeshTransform::Load(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	m_Pos = new glm::vec3(pos);
	m_Rot = new glm::vec3(rot);
	m_Scale = new glm::vec3(scale);
	m_Angle = 0.0f; 
	Model = glm::mat4(1.0f);
}

void MeshTransform::Destroy(void)
{
	if (m_Pos) delete m_Pos;
	if (m_Rot) delete m_Rot;
	if (m_Scale) delete m_Scale;
}

/*
TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
*/

glm::vec3 *MeshTransform::GetPos()   { return m_Pos; }
glm::vec3 *MeshTransform::GetRot()   { return m_Rot; }
glm::vec3 *MeshTransform::GetScale() { return m_Scale; }
void MeshTransform::SetPos(glm::vec3 pos)     { m_Pos->x = pos.x; m_Pos->y = pos.y; m_Pos->z = pos.z; }
void MeshTransform::SetRot(glm::vec3 rot, float angle)     { m_Rot->x = rot.x; m_Rot->y = rot.y; m_Rot->z = rot.z; m_Angle = angle; }
void MeshTransform::SetScale(glm::vec3 scale) { m_Scale->x = scale.x; m_Scale->y = scale.y; m_Scale->z = scale.z; }
//void MeshTransform::Translate(glm::vec3 v) { Model = glm::translate(Model, v); }
//void MeshTransform::Rotate(glm::vec3 v, float Angle) { Model =  glm::rotate(Model, Angle, v); }
//void MeshTransform::Scale(glm::vec3 v) { Model = glm::scale(Model, v); }

glm::mat4 MeshTransform::GetModel()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_Pos->x, m_Pos->y, m_Pos->z));
	model = glm::rotate(model, glm::radians(m_Angle), glm::vec3(m_Rot->x, m_Rot->y, m_Rot->z));
	model = glm::scale(model, glm::vec3(m_Scale->x, m_Scale->y, m_Scale->z));

	return model;
}
