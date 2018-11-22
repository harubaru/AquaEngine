#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec2 TexCoord;
	vec3 Normal;
	vec3 FragPos;
	vec4 FragPosLightSpace; // light transformations
} fs_in;

struct directionallight {
	vec3 Position;
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
}; uniform directionallight DirectionalLight;

uniform int shadowFiltering;
uniform int shadowsEnabled;
uniform int fullbright;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

float ShadowCalculation()
{
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightDir = normalize(DirectionalLight.Direction - fs_in.FragPos);
    	vec3 projCoords = fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
    	projCoords = projCoords * 0.5 + 0.5;
	if(projCoords.z > 1.0)
		return 0.0;

    	float closestDepth = texture(shadowMap, projCoords.xy).r; 
    	float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

	float shadow = 0.0;

	if (shadowFiltering != 0) {
		vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
		for (float x = -1.5; x <= 1.5; ++x) {
			for (float y = -1.5; y <= 1.5; ++y) {
        		    	float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
        			shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        		}    
    		}
    		shadow /= 16.0;
	} else {
		shadow = currentDepth > closestDepth ? 1.0 : 0.0;
	}

    	return shadow;
}  

vec3 Calculate_DirectionalLight(vec4 color)
{
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(1);

	// Ambient Lighting
	vec3 ambient = 1 * color.rgb;

	// Diffuse Lighting
	vec3 lightDir = normalize(DirectionalLight.Direction);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	// Calculate Shadows
	float shadow = 0.0;

	if (shadowsEnabled == 1)
		shadow = ShadowCalculation();

	return (ambient + (1.0 - shadow) * diffuse) * color.rgb;    
}

void main()
{   
	vec4 color = texture(diffuseTexture, fs_in.TexCoord);

	if (color.a < 0.1)
		discard;
	if (fullbright == 0)
		color = vec4(Calculate_DirectionalLight(color), 1.0);

    	Fragment = color;
}