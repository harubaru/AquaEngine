#ifndef SHADOWMAPPING_H
#define SHADOWMAPPING_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

void ShadowMapping_Init(Shader &shader);
void ShadowMapping_RenderDirectionalShadow(glm::vec3 light_pos, Shader &shader);
void ShadowMapping_RenderReset(int w, int h);
void ShadowMapping_RenderToScreen(bool debug);

void ShadowMapping_Bind(void);
void ShadowMapping_Unbind(void);


#endif
