#include <stdlib.h>
#include <iostream>
#include <vector>
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

	Display display(1280, 800, "AquaGL", SDL_WINDOW_RESIZABLE);
	Graphics graphics(display);

	int Width, Height;
	display.GetSize(&Width, &Height);

	Camera camera(glm::vec3(0, 2, -10), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);

	Shader shader("./resources/shaders/primitives/vert_mesh.glsl", "./resources/shaders/primitives/frag_mesh.glsl");
	MeshTransform mt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
	Texture tex("./resources/textures/BrickWall.jpg");
	Model cone("./resources/meshes/Cone.obj");
	Model cube("./resources/meshes/Cube.obj");

	while(!display.Close) {
		display.Update();
		graphics.Clear(0.0, 0.0, 0.0);

		mt.Rotate(glm::vec3(0, 1, 0), 0.016 * 1);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());
		shader.SetCameraPos(camera.GetPos());

		display.GetSize(&Width, &Height);
		camera.Update(glm::vec3(0, 2, -10), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);

		tex.Bind(0);
		cube.Render();
		cone.Render();
		tex.Unbind();

		shader.Unbind();
	}

	return 0;
}
