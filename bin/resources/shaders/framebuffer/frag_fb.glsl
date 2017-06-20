#version 330 core

in vec2 TexCoord;
out vec4 Color;

uniform sampler2D tex;

void main()
{
	Color = vec4(0.3 - texture(tex, TexCoord).rgb, 1.0);
}
