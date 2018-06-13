#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 LightSpaceMatrix;

out VS_OUT {
	vec3 Normal;
	vec2 TexCoord;
	vec3 FragPos;
	vec4 FragPosLightSpace;
} vs_out;

void main()
{
	vs_out.Normal = mat3(transpose(inverse(Model))) * normal;
	vs_out.TexCoord = texcoord;
	vs_out.FragPos = vec3(Model * vec4(position, 1.0));
	vs_out.FragPosLightSpace = LightSpaceMatrix * vec4(vs_out.FragPos, 1.0);

	gl_Position = Projection * View * Model * vec4(position, 1.0);
}
