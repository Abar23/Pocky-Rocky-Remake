#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec3 camPos;
void main(void)
{
    gl_Position = vec4(aPos.x - camPos.x, aPos.y - camPos.y, aPos.z - camPos.z, 1.0) ;
    TexCoord = aTexCoord;
}