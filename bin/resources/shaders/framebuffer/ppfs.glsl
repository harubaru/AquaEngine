#version 330 core

in vec2 TexCoord;
out vec4 Color;

uniform sampler2D tex;

void main()
{
	Color = texture(tex, TexCoord) * vec4(0.1, 0.1, 1, 1);
}
