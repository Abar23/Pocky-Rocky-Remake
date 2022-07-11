#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D entityTexture;
uniform vec2 FrameOffset;

void main(void){

vec4 texColor = texture(entityTexture, TexCoord+FrameOffset);
if (texColor.a < 0.1) discard;
FragColor = texColor;
} 