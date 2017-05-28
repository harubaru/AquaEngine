#include <stdlib.h>
#include <iostream>
#include <vector>
#include <graphics/Graphics.h>
#include <graphics/Mesh.h>
#include <graphics/MeshTransform.h>
#include <graphics/Texture.h>
#include <graphics/Camera.h>
#include <file/obj.h>

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
		Vertex( 0.0f,   1.0f, 0.0f, 1.0f, 0.0f ), 
		Vertex( 1.0f,  -1.0f, 0.0f, 0.5f, 1.0f )
	};	
	
	std::vector<GLuint> indices = { 0, 1, 2 };

	Camera camera(glm::vec3(0, 0, -3), 70.0f, 800.0f / 600.0f, 0.01f, 1000.0f);

	Shader shader("./resources/shaders/primitives/vert_quad.glsl", "./resources/shaders/primitives/frag_quad.glsl");
	Mesh triangle(vertices, indices);
	MeshTransform mt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
	Texture tex("./resources/textures/BrickWall.jpg");
		
	std::vector<glm::vec3> mesh_vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<unsigned int> mesh_indices;
	bool res = ParseOBJFile("./resources/meshes/cube.obj", mesh_vertices, normals, texcoords, indices);
	if(!res)
		(void)res;
		
	while(!display.Close) {
		display.Update();
		graphics.Clear(0.0, 0.1, 0.1);
		
		mt.Rotate(glm::vec3(0, 1, 0), 0.016 * 1);

		shader.Bind();
		shader.SetModel(mt.GetModel());
		shader.SetProjection(camera.GetProjection());
		shader.SetView(camera.GetView());
		shader.SetQuadColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

		tex.Bind(0);	
		triangle.Draw();
		tex.Unbind();
		shader.Unbind();
	}

	return 0;
}

