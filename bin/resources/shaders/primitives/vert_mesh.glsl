#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vec3 Normal;
out vec2 TexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	Normal = normal;
	TexCoord = texcoord;
	gl_Position = Projection * View * Model * vec4(position, 1.0);
}
