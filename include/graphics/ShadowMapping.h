#ifndef SHADOWMAPPING_H
#define SHADOWMAPPING_H

#include <export.h>

#include <iostream>
#include <vector>
#include <graphics/gl3w.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>

#include <core/ConVar.h>

API void ShadowMapping_Init(Shader &shader);
API void ShadowMapping_RenderDirectionalShadow(glm::vec3 light_pos, glm::vec3 light_dir, Shader &shader);
API void ShadowMapping_RenderReset(int w, int h);
API void ShadowMapping_RenderToScreen(bool debug); // deprecated

API void ShadowMapping_Bind(void);
API void ShadowMapping_Unbind(void);


#endif
