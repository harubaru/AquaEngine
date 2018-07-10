#version 330 core

in vec2 TexCoord;
out vec4 Color;

uniform sampler2D tex;

vec3 none()
{
	return vec3(texture(tex, TexCoord).rgb);
}

vec3 sharpen()
{
	float offset = 1.0 / 300.0; 

	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset), // top-left
		vec2( 0.0f,    offset), // top-center
		vec2( offset,  offset), // top-right
		vec2(-offset,  0.0f),   // center-left
		vec2( 0.0f,    0.0f),   // center-center
		vec2( offset,  0.0f),   // center-right
		vec2(-offset, -offset), // bottom-left
		vec2( 0.0f,   -offset), // bottom-center
		vec2( offset, -offset)  // bottom-right    
	);

	float kernel[9] = float[](
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
    	);
    
	/* Sample the texture */
    	vec3 sample[9];
    	for(int i = 0; i < 9; i++)
		sample[i] = vec3(texture(tex, TexCoord.st + offsets[i]));

	/* Apply the post processing effect */
    	vec3 res = vec3(0.0);
    	for(int i = 0; i < 9; i++)
		res += sample[i] * kernel[i];

	return res;
}

vec3 fxaa()
{
	return vec3(0);
}

void main()
{
	Color = vec4(none(), 1.0);
}
