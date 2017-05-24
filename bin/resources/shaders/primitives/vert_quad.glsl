#version 330

layout(location = 0) in vec3 position;

varying vec4 PrimitiveColor;
varying vec2 TexCoord;

void main()
{
	gl_Position = vec4(position, 1.0);
}

