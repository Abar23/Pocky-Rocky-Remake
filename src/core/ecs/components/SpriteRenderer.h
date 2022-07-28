#pragma once

#include "shader.h"
#include "math/Vec3.h"
#include <GLFW/glfw3.h>

struct SpriteRenderer
{
	Shader* shader;
	GLuint vao;
	int textureID;
	
	int columns;
	int currentFrame;

	float frameWidth;
	float frameHeight;

	vec3 cameraPosition; //this is temporary
};