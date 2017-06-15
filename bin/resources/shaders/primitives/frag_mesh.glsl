#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirLight dirlight;

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	float cutoff;
	float outercutoff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// customizable constants
#define MAX_POINT_LIGHTS 100

uniform PointLight PointLights[MAX_POINT_LIGHTS];
uniform int NumLights;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

layout (location = 0) out vec4 Color;

uniform vec4 QuadColor;
uniform vec3 CameraPos;
uniform sampler2D sample;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewdir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragpos, vec3 viewdir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragpos, vec3 viewdir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewdir = normalize(CameraPos - FragPos);

//	vec3 result = CalcDirLight(dirlight, norm, viewdir);
	vec3 result;

	for(int i = 0; i < NumLights; i++)
		result += CalcPointLight(PointLights[i], norm, FragPos, viewdir);

	result = pow(result, vec3(1.0 / 1.5));
	Color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewdir)
{
	vec3 LightDirection = normalize(-light.direction);

	// diffuse
	float diff = max(dot(normal, LightDirection), 0.0);

	// specular
	vec3 reflectdir = reflect(-LightDirection, normal);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragpos, vec3 viewdir)
{
	vec3 LightDirection = normalize(light.position - fragpos);

	//diffuse
	float diff = max(dot(normal, LightDirection), 0.0);

	//specular
	vec3 reflectdir = reflect(-LightDirection, normal);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);

	//attenuation
	float distance = length(light.position - fragpos);
	float attenuation = 1.0 / (distance * distance);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragpos, vec3 viewdir)
{
	vec3 LightDirection = normalize(light.position - fragpos);

	// diffuse
	float diff = max(dot(normal, LightDirection), 0.0);

	// specular
	vec3 reflectdir = reflect(-LightDirection, normal);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - fragpos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// intensity
	float theta = dot(LightDirection, normalize(-light.direction));
	float epsilon = light.cutoff - light.outercutoff;
	float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}
