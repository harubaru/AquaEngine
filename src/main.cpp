#include <stdlib.h>
#include <iostream>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>
#include <graphics/MeshTransform.h>
#include <graphics/Texture.h>

using namespace std;

int main(int argv, char** args)
{
	(void)argv;
	(void)args;

	Display display(800, 600, "AquaGL");
	Graphics graphics(display);
		
	Vertex vertices[] = {
		//      x       y     z     tex coords
		Vertex( -1.0f, -1.0f, 0.0f, 0.0f, 0.0f ), 
		Vertex( 0.0f, 1.0f, 0.0f, 1.0f, 0.0f ), 
		Vertex( 1.0f, -1.0f, 0.0f, 0.5f, 1.0f )
	};	

	Shader shader("./resources/shaders/primitives/vert_quad.glsl", "./resources/shaders/primitives/frag_quad.glsl");
	Mesh triangle(vertices, sizeof(vertices)/sizeof(vertices[0]));
	MeshTransform mt(glm::vec3(200, 200, 0), glm::vec3(0, 0, 1), glm::vec3(100, 100, 0));
	Texture tex("./resources/textures/BrickWall.jpg");
	
	glm::mat4 Projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	while(!display.Close) {
		display.Update();
		graphics.Clear(0.0, 0.1, 0.1);
		
		shader.Bind();
		shader.SetProjection(Projection);
		shader.SetModel(mt.GetModel());
		shader.SetQuadColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

		tex.Bind(0);	
		triangle.Draw();
		tex.Unbind();
		shader.Unbind();
	}

	return 0;
}

