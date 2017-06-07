#include <stdlib.h>
#include <iostream>
#include <vector>
#include <util/Clock.h>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>
#include <graphics/MeshTransform.h>
#include <graphics/Model.h>
#include <graphics/Texture.h>
#include <graphics/Camera.h>

using namespace std;

int main(int argv, char** args)
{
	(void)argv;
	(void)args;

	Clock clock;
	Clock_Initialize(&clock);

	Display display(1280, 800, "AquaGL", SDL_WINDOW_RESIZABLE);
	Graphics graphics(display);

	int Width, Height;
	display.GetSize(&Width, &Height);

	Camera camera(glm::vec3(0, 2, -10), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);

	Shader shader("./resources/shaders/primitives/vert_mesh.glsl", "./resources/shaders/primitives/frag_mesh.glsl");
	MeshTransform mt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
	Texture tex("./resources/textures/BrickWall.jpg");
	Model cube("./resources/meshes/Cube.obj");

	while(!display.Close) {
		Clock_TickBegin(&clock);

		display.Update();
		graphics.Clear(0.0, 0.0, 0.0);

		mt.Rotate(glm::vec3(0, 1, 0), (float)clock.DeltaTime * 1);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());

		shader.SetVec3("CameraPos", camera.GetPos());
		shader.SetVec3("LightPos", glm::vec3(2.0, 2.0, -8.0));

		display.GetSize(&Width, &Height);
		camera.Update(glm::vec3(0, 0, -5), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);

		tex.Bind(0);
		cube.Render();
		tex.Unbind();

		shader.Unbind();

		Clock_TickEnd(&clock);
	}

	return 0;
}
