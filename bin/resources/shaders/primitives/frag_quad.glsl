#version 330

in vec2 TexCoord;

layout (location = 0) out vec4 Color;

uniform sampler2D sampler;

void main()
{
	Color = mix(vec4(1.0, 0.0, 0.0, 1.0), texture2D(sampler, TexCoord), 1.0);
//	Color = vec4(1.0, 0.0, 0.0, 1.0);
}

