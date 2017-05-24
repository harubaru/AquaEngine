#include <stdlib.h>
#include <iostream>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>
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
	Texture tex("./resources/textures/BrickWall.jpg");

	while(!display.Close) {
		display.Update();
		graphics.Clear(0.2, 0.2, 0.2);
		
		shader.Bind();
		tex.Bind(0);	
		triangle.Draw();
		tex.Unbind();
		shader.Unbind();
	}

	return 0;
}

