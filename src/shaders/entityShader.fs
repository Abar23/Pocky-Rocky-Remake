#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D entityTexture;
uniform vec2 FrameOffset;

void main(void){

FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
FragColor = texture(entityTexture, TexCoord+FrameOffset);
} 