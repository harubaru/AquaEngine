#version 330 core

in vec2 TexCoord;
out vec4 Color;

uniform sampler2D Text;
uniform vec3 TextColor;

void main()
{
	Color = vec4(TextColor, 1.0) * vec4(1.0, 1.0, 1.0, texture2D(Text, TexCoord).r);
}
