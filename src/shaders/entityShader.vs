#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec3 camPos;
uniform vec2 entityPos;
uniform vec2 scale;
void main(void)
{
    gl_Position = vec4((scale.x*aPos.x - camPos.x + entityPos.x), (scale.y*aPos.y - camPos.y + entityPos.y), aPos.z - camPos.z, 1.0) ;
    TexCoord = aTexCoord;
} 