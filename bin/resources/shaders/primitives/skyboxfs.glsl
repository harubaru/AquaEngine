#version 330 core

in vec3 TexCoord;

out vec4 Color;

uniform samplerCube skybox;

void main()
{
        Color = texture(skybox, TexCoord);
//        Color = vec4(0.2, 0.4, 0.6, 1.0);
}
