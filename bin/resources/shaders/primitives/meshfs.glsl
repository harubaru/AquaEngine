#version 330 core

out vec4 Fragment;

in VS_OUT {
	vec3 Normal;
	vec2 TexCoord;
	vec3 FragPos;
	vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation()
{
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    	// perform perspective divide
    	vec3 projCoords = fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
    	// transform to [0,1] range
    	projCoords = projCoords * 0.5 + 0.5;
    	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    	float closestDepth = texture(shadowMap, projCoords.xy).r; 
    	// get depth of current fragment from light's perspective
    	float currentDepth = projCoords.z;
    	// check whether current frag pos is in shadow
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    	return shadow;
}  

void main()
{           
	vec4 color = texture(diffuseTexture, fs_in.TexCoord);

	if (color.a < 0.1)
		discard;

	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(1);

	// Ambient Lighting
	vec3 ambient = 1 * color.rgb;

	// Diffuse Lighting
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular Lighting
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
	vec3 specular = spec * lightColor;    

	// Calculate Shadows
	float shadow = ShadowCalculation();       
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color.rgb;    



    	Fragment = vec4(lighting, 1.0);
}