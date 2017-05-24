#ifndef AQUAGL_MESHTRANSFORM_H
#define AQUAGL_MESHTRANSFORM_H

#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

class MeshTransform {
private:
	glm::vec3 m_Pos, m_Rot, m_Scale;
	float m_Angle;
public:
	MeshTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) 
		: m_Pos(pos), m_Rot(rot), m_Scale(scale), m_Angle(0) {}

	inline glm::vec3 GetPos()   { return m_Pos; }
	inline glm::vec3 GetRot()   { return m_Rot; }
	inline glm::vec3 GetScale() { return m_Scale; }

	inline void SetPos(glm::vec3 pos)     { m_Pos = pos; }
	inline void SetRot(glm::vec3 rot, float angle)     { m_Rot = rot; m_Angle = angle; }
	inline void SetScale(glm::vec3 scale) { m_Scale = scale; }

	glm::mat4 GetModel();
};

#endif

