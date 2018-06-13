#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <vector>
#include <algorithm>

#include <core/PhysEntity.h>

#include <graphics/Display.h>
#include <graphics/Shader.h>
#include <graphics/Camera.h>
#include <graphics/ShadowMapping.h>
#include <graphics/Framebuffer.h>
#include <graphics/Display.h>

class SceneRenderer {
private:
	Shader shaders[3];
	Framebuffer fb;
	std::vector<PhysEntity> renderlist;
public:
	SceneRenderer(int w, int h);

	void Add(PhysEntity &ent);
	void Remove(PhysEntity &ent);

	void Update(Display &display, Camera &camera);
};

#endif
