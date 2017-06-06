#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	Normal = mat3(transpose(inverse(Model))) * normal;
	TexCoord = texcoord;
	FragPos = vec3(Model * vec4(position, 1.0));
	gl_Position = Projection * View * Model * vec4(position, 1.0);
}
