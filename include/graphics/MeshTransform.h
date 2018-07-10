#ifndef AQUAENGINE_GRAPHICS_MESHTRANSFORM_H
#define AQUAENGINE_GRAPHICS_MESHTRANSFORM_H

#include <export.h>

#include <iostream>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

using namespace glm;

class API MeshTransform {
private:
	glm::vec3 *m_Pos, *m_Rot, *m_Scale;
	glm::mat4 Model;
	float m_Angle;
public:
	MeshTransform() {}
	MeshTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) { Load(pos, rot, scale); }
//	~MeshTransform() { delete m_Pos; delete m_Rot; delete m_Scale; }

	void Load(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	void Destroy(void);

	glm::vec3 *GetPos();
	glm::vec3 *GetRot();
	glm::vec3 *GetScale();

	void SetPos(glm::vec3 pos);
	void SetRot(glm::vec3 rot, float angle);
	void SetScale(glm::vec3 scale);

//	void Translate(glm::vec3 v);
//	void Rotate(glm::vec3 v, float Angle);
//	void Scale(glm::vec3 v);

	glm::mat4 GetModel();
};

#endif

