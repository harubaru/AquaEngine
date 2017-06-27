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

#include <core/Input.h>

#undef main

using namespace std;

int main(int argv, char** args)
{
	(void)argv;
	(void)args;

	Clock clock;
	Clock_Initialize(&clock);

	Display display(1280, 800, "AquaEngine", 0);
	Graphics graphics(display);
	Input InputHandler;

	int Width, Height;
	display.GetSize(&Width, &Height);

	TextRenderer TextHandler(1280, 800);
	TextHandler.LoadFont("./resources/fonts/FreeSans.ttf", 13);

	Camera camera(glm::vec3(4, 5, -10), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);

	Shader shader("./resources/shaders/primitives/vert_mesh.glsl", "./resources/shaders/primitives/frag_mesh.glsl");
	MeshTransform mt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
	Texture diff("./resources/textures/WoodPlanksDiffuseMap.jpg", GL_TEXTURE_2D);
	Texture spec("./resources/textures/WoodPlanksSpecularMap.png", GL_TEXTURE_2D);
	Model cube("./resources/meshes/Cube.obj");
	Model plane("./resources/meshes/Plane.obj");

	shader.Bind();
	// material configuration
	shader.SetInt("material.diffuse", 0); // tex 1
	shader.SetInt("material.specular", 1); // tex 2
	shader.SetFloat("material.shininess", 32.0f);

	// directional light configuration
	shader.SetVec3("dirlight.direction", glm::vec3(0.0f, 1.0f, 5.0f));
	shader.SetVec3("dirlight.ambient", glm::vec3(0.05f, 0.06f, 0.07f));
	shader.SetVec3("dirlight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.SetVec3("dirlight.specular", glm::vec3(0.5f, 0.0f, 0.0f));

	// pointlight configuration
	shader.SetVec3("PointLights[0].position", glm::vec3(3.0f, 1.0f, 0.0f));
	shader.SetVec3("PointLights[0].ambient", glm::vec3(0.05, 0.00, 0.00));
	shader.SetVec3("PointLights[0].diffuse", glm::vec3(0.25, 0.0, 0.0));
	shader.SetVec3("PointLights[0].specular", glm::vec3(1.0, 0.0, 0.0));
	shader.SetInt("PointLights[0].render", 1);

	shader.SetVec3("PointLights[1].position", glm::vec3(0.0f, 1.0f, 0.0f));
	shader.SetVec3("PointLights[1].ambient", glm::vec3(0.0, 0.05, 0.0));
	shader.SetVec3("PointLights[1].diffuse", glm::vec3(0.0, 0.25, 0.0));
	shader.SetVec3("PointLights[1].specular", glm::vec3(0.0, 1.0, 0.0));
	shader.SetInt("PointLights[1].render", 1);

	shader.SetVec3("PointLights[2].position", glm::vec3(-3.0f, 1.0f, 0.0f));
	shader.SetVec3("PointLights[2].ambient", glm::vec3(0.00, 0.0, 0.05));
	shader.SetVec3("PointLights[2].diffuse", glm::vec3(0.0, 0.0, 0.25));
	shader.SetVec3("PointLights[2].specular", glm::vec3(0.0, 0.0, 1.0));
	shader.SetInt("PointLights[2].render", 1);

	shader.SetInt("NumLights", 3);
	shader.Unbind();

	mt.Translate(glm::vec3(0, -0.25, -0));

	Framebuffer fb(Width, Height);

	float x = 5;
	float y = -10;
	float counter = 0.0;
	while(InputHandler.m_WindowClose == false) {
		Clock_TickBegin(&clock);
		Clock_TickEnd(&clock);
		graphics.GetGLError();

		x = sin(counter * 2);
		counter += 0.01f;

		camera.Update(90.0, -30.0, glm::vec3(x, 3, y), 70.0f, (float)Width / (float)Height, 0.1f, 100.0f);
		fb.Bind();
		graphics.Clear(0.0, 0.0, 0.0);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());

		shader.SetVec3("CameraPos", camera.GetPos());

		display.GetSize(&Width, &Height);

		diff.Bind(0);
		spec.Bind(1);
		plane.Render();
		spec.Unbind();
		diff.Unbind();

		shader.Unbind();

		TextHandler.RenderText("AquaEngine 0.0.0-PreAlpha", 10.0f, 10.0f, 1.0f, glm::vec3(1.0));

		fb.Unbind();
		fb.Draw(); 

		display.Update();
		InputHandler.Update();
	}

	return 0;
}
