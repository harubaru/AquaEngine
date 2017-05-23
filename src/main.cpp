#include <stdlib.h>
#include <iostream>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>

using namespace std;

int main(int argv, char** args)
{
	(void)argv;
	(void)args;

	Display display(800, 600, "AquaGL");
	Graphics graphics(display);
	
	Vertex vertices[] = {
		Vertex(0, 1, 0),
		Vertex(1, -1, 0),
		Vertex(-1, -1, 0)
	};

	Shader shader("./resources/shaders/primitives/vert_quad.glsl", "./resources/shaders/primitives/frag_quad.glsl");
	Mesh triangle(vertices, 3);

	while(!display.Close) {
		display.Update();
		graphics.Clear(0.1, 0.1, 0.1);
		
		shader.Bind();
		triangle.Draw();
		shader.Unbind();
	}

	return 0;
}

