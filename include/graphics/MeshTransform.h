#ifndef AQUAENGINE_GRAPHICS_MESHTRANSFORM_H
#define AQUAENGINE_GRAPHICS_MESHTRANSFORM_H

#include <iostream>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

using namespace glm;

class MeshTransform {
private:
	glm::vec3 m_Pos, m_Rot, m_Scale;
	glm::mat4 Model;
	float m_Angle;
public:
	MeshTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) 
		: m_Pos(pos), m_Rot(rot), m_Scale(scale), m_Angle(0.0)
	{ Load(pos, rot, scale); }

	MeshTransform() 
		: m_Pos(glm::vec3(0.0, 0.0, 0.0)), m_Rot(glm::vec3(0.0, 0.0, 1.0)), m_Scale(glm::vec3(1.0, 1.0, 1.0)), m_Angle(0.0) {}

	inline void Load(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	{
		m_Pos = pos; m_Rot = rot; m_Scale = scale; m_Angle = 0.0f; 
	
		Model = glm::mat4(1.0f);

		Model = glm::translate(Model, pos);
		Model = glm::scale(Model, scale);
	}

	inline glm::vec3 GetPos()   { return m_Pos; }
	inline glm::vec3 GetRot()   { return m_Rot; }
	inline glm::vec3 GetScale() { return m_Scale; }

	inline void SetPos(glm::vec3 pos)     { m_Pos = pos; }
	inline void SetRot(glm::vec3 rot, float angle)     { m_Rot = rot; m_Angle = angle; }
	inline void SetScale(glm::vec3 scale) { m_Scale = scale; }

	inline void Translate(glm::vec3 v) { Model = glm::translate(Model, v); }
	inline void Rotate(glm::vec3 v, float Angle) { Model =  glm::rotate(Model, Angle, v); }
	inline void Scale(glm::vec3 v) { Model = glm::scale(Model, v); }

	inline glm::mat4 GetModel() { return Model; }
};

#endif

