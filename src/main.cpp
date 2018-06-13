#include <stdlib.h>
#include <iostream>
#include <vector>
#include <util/Clock.h>
#include <cmath>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>
#include <graphics/MeshTransform.h>
#include <graphics/Model.h>
#include <graphics/Texture.h>
#include <graphics/Camera.h>
#include <graphics/Framebuffer.h>
#include <graphics/Skybox.h>
#include <graphics/TextRenderer.h>
#include <graphics/ShadowMapping.h>

#include <core/PhysEntity.h>
#include <core/Input.h>
#include <core/SceneRenderer.h>

#undef main
using namespace std;

int main()
{
	Display display(1280, 800, "Barack Obama", 16, 0);
	Graphics graphics(display);
	Input InputHandler;
	Clock clock;
	Clock_Initialize(&clock);

	int Width, Height;
	display.GetSize(&Width, &Height);

	Camera camera(glm::vec3(4, 5, -10), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);
	camera.LockCursor();

	PhysEntity plane("./resources/meshes/Cube.obj", "./resources/textures/WoodPlanksDiffuseMap.jpg", vec3(0, 0, 0), vec3(0, 0, 1), vec3(10, 1, 10));
	PhysEntity ent("./resources/meshes/Cube.obj", "./resources/textures/WoodPlanksDiffuseMap.jpg", vec3(0, 4, 5), vec3(0, 0, 1), vec3(1, 1, 1));
	PhysEntity grass("./resources/meshes/Foliage.obj", "./resources/textures/tallgrass.png", vec3(0, 1, 0), vec3(0, 0, 1), vec3(1));

	SceneRenderer scenemgr(1280, 800);
	scenemgr.Add(grass);
	scenemgr.Add(plane);
	scenemgr.Add(ent);

	while(!InputHandler.m_WindowClose) {
		Clock_TickBegin(&clock);
		graphics.Clear();
		scenemgr.Update(display, camera);
		display.Update();
		InputHandler.Update();
		Clock_TickEnd(&clock);
		camera.Update(display, clock.DeltaTime, glm::vec3(-5, 3, 0), 90.0f, (float)Width / (float)Height, 0.1f, 100.0f);
	}

	return 0;
}
