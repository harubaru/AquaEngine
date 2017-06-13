#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

layout (location = 0) out vec4 Color;

uniform vec4 QuadColor;
uniform vec3 CameraPos;
uniform vec3 LightPos;
uniform sampler2D sample;

void main()
{
	vec4 Texel = texture(sample, TexCoord);
	if(Texel.a < 0.1)
		discard;

	vec3 LightColor = vec3(1.0, 1.0, 1.0);

	// Calculate Ambient
	float AmbientStrength = 0.01;
	vec3 Ambient = AmbientStrength * LightColor;

	// Calculate Diffuse
	vec3 Norm = normalize(Normal);
	vec3 LightDirection = normalize(LightPos - FragPos);
	float Diff = max(dot(Norm, LightDirection), 0.0);
	vec3 Diffuse = Diff * LightColor;

	// Calculate Specular
	float SpecularStrength = 1;
	vec3 ViewDirection = normalize(CameraPos - FragPos);
	vec3 ReflectDirection = reflect(-LightDirection, Norm);
	float Spec = pow(max(dot(ViewDirection, ReflectDirection), 0.0), 32);
	vec3 Specular = vec3(SpecularStrength * Spec * LightColor);

	vec4 ProcColor = vec4(Ambient + Diffuse + Specular, 1.0) * Texel;

	Color = ProcColor;
}
