#version 330 core

layout (location = 0) in vec3 position;

out vec3 TexCoord;

uniform mat4 Projection;
uniform mat4 View;

void main()
{
        TexCoord = position;
        vec4 pos = Projection * View * vec4(position, 1.0);
        gl_Position = pos.xyww;
}
