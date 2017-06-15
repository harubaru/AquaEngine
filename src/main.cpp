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
#include <graphics/Framebuffer.h>
#include <graphics/Skybox.h>

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
	Texture diff("./resources/textures/BrickWallDiffuseMap.jpg", GL_TEXTURE_2D);
	Texture spec("./resources/textures/BrickWallSpecularMap.png", GL_TEXTURE_2D);
	Model cube("./resources/meshes/Cube.obj");

	Shader skyboxshader("./resources/shaders/primitives/vert_skybox.glsl", "./resources/shaders/primitives/frag_skybox.glsl");

	std::vector<std::string> Faces = {
		"./resources/textures/skybox/miramar_rt.tga",
		"./resources/textures/skybox/miramar_lf.tga",
		"./resources/textures/skybox/miramar_up.tga",
		"./resources/textures/skybox/miramar_dn.tga",
		"./resources/textures/skybox/miramar_bk.tga",
		"./resources/textures/skybox/miramar_ft.tga"
	};

	Skybox skybox(Faces, skyboxshader, cube);

	shader.Bind();
	// material configuration
	shader.SetInt("material.diffuse", 0);
	shader.SetInt("material.specular", 1);
	shader.SetFloat("material.shininess", 32.0f);

	// directional light configuration
	shader.SetVec3("dirlight.direction", glm::vec3(0.0f, 1.0f, 5.0f));
	shader.SetVec3("dirlight.ambient", glm::vec3(0.5f, 0.6f, 0.7f));
	shader.SetVec3("dirlight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.SetVec3("dirlight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// pointlight configuration
	shader.SetVec3("PointLights[0].position", glm::vec3(0.0f, 1.0f, 5.0f));
	shader.SetVec3("PointLights[0].ambient", glm::vec3(0.05, 0.05, 0.05));
	shader.SetVec3("PointLights[0].diffuse", glm::vec3(0.8, 0.8, 0.8));
	shader.SetVec3("PointLights[0].specular", glm::vec3(1.0, 1.0, 1.0));
	shader.SetFloat("PointLights[0].constant", 2.0);
	shader.SetFloat("PointLights[0].linear", 0.09);
	shader.SetFloat("PointLights[0].quadratic", 0.032);

	shader.SetInt("NumLights", 1);
	shader.Unbind();

	while(!display.Close) {
		Clock_TickBegin(&clock);
		graphics.GetGLError();

		display.Update();
		graphics.Clear(0.0, 0.0, 0.0);

		mt.Rotate(glm::vec3(1, 1, 0), (float)clock.DeltaTime * 1);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());

		shader.SetVec3("CameraPos", camera.GetPos());

		display.GetSize(&Width, &Height);
		camera.Update(0.0, 0.0, glm::vec3(0, 0, -5), 70.0f, (float)Width / (float)Height, 0.01f, 100.0f);

		diff.Bind(0);
		spec.Bind(1);
		cube.Render();
		spec.Unbind();
		diff.Unbind();

		shader.Unbind();

		skybox.Draw(camera);

		Clock_TickEnd(&clock);
	}

	return 0;
}
