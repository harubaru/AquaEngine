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

	Display display(800, 600, "AquaGL");
	Graphics graphics(display);

	Camera camera(glm::vec3(0, 2, -10), 70.0f, 800.0f / 600.0f, 0.01f, 1000.0f);

	Shader shader("./resources/shaders/primitives/vert_mesh.glsl", "./resources/shaders/primitives/frag_mesh.glsl");
	MeshTransform mt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
	Texture tex("./resources/textures/BrickWall.jpg");
	Model model("./resources/meshes/Cone.obj");

	while(!display.Close) {
		display.Update();
		graphics.Clear(0.0, 0.0, 0.0);

		mt.Rotate(glm::vec3(0, 1, 0), 0.016 * 1);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());
		shader.SetQuadColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

		tex.Bind(0);
		model.Render();
		tex.Unbind();
		shader.Unbind();
	}

	return 0;
}
