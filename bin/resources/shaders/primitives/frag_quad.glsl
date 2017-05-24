#version 330

varying vec4 PrimitiveColor;
varying vec2 TexCoord;

void main()
{
	gl_FragColor = PrimitiveColor;
}

