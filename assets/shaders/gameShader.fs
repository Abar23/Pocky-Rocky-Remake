#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D mapTexture;

void main(void){
vec4 texColor = texture(mapTexture, TexCoord);
if (texColor.a < 0.1) discard;
FragColor = texColor;
} 