#version 330

in vec2 TexCoord;

layout (location = 0) out vec4 Color;

uniform vec4 QuadColor;
uniform sampler2D sampler;

void main()
{
	vec4 ProcColor = mix(QuadColor, texture2D(sampler, TexCoord), 1.0);

	if(ProcColor.a < 0.1)
		discard;

	Color = ProcColor;
}

