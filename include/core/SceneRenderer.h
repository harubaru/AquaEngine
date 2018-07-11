#ifndef AQUAENGINE_CORE_SCENERENDERER_H
#define AQUAENGINE_CORE_SCENERENDERER_H

#include <export.h>

#include <vector>
#include <algorithm>

#include <core/ConVar.h>
#include <core/SceneObject.h>

#include <graphics/Display.h>
#include <graphics/Shader.h>
#include <graphics/Camera.h>
#include <graphics/ShadowMapping.h>
#include <graphics/Framebuffer.h>
#include <graphics/Display.h>
#include <graphics/Skybox.h>
#include <graphics/Map.h>

class API SceneRenderer {
private:
	Shader shaders[4];
	Framebuffer fb;
	Skybox *skybox;
	Map *map;
	std::vector<SceneObject> renderlist;
public:
	SceneRenderer() { Load(); }

	void Load();

	void AddObject(SceneObject &object);
	void RemoveObject(SceneObject &object);

	void AddSkybox(Skybox &skybox);
	void AddMap(Map &map);

	void Update(Display &display, Camera &camera);
};

#endif
