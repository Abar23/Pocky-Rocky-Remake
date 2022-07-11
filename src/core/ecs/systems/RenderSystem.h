#pragma once

#include "core/ecs/components/Transform.h"
#include "core/ecs/components/SpriteRenderer.h"
#include "core/ecs/framework/AbstractSystem.h"
#include "locators/EcsLocator.h"

class RenderSystem : public AbstractSystem
{
public:
	void Update(float dt)
	{
		EcsManager* ecsManager = EcsLocator::GetEcsManager();
		for (auto const& entity : entities)
		{
			auto& transform = ecsManager->GetComponent<Transform>(entity);
			auto const& spriteRenderer = ecsManager->GetComponent<SpriteRenderer>(entity);


			spriteRenderer.shader->use();
			// sets the texture
			spriteRenderer.shader->setInt("entityTexture", spriteRenderer.textureID);
			int currentRow = spriteRenderer.currentFrame / spriteRenderer.columns;
			int currentColumn = spriteRenderer.currentFrame % spriteRenderer.columns;
			glUniform2f(
				glGetUniformLocation(spriteRenderer.shader->ID, "FrameOffset"), 
				currentColumn * spriteRenderer.frameWidth,
				-currentRow * spriteRenderer.frameHeight);

			// camera stuff
			glUniform3f(glGetUniformLocation(spriteRenderer.shader->ID, "camPos"), 
				spriteRenderer.cameraPosition.x, 
				spriteRenderer.cameraPosition.y, 
				spriteRenderer.cameraPosition.z); // this needs to be a matrix

			glUniform2f(glGetUniformLocation(spriteRenderer.shader->ID, "entityPos"), 
				transform.position.x, 
				transform.position.y);

			glUniform2f(glGetUniformLocation(spriteRenderer.shader->ID, "scale"), 1.0f, 1.0f); //scale should be removed as a uniform eventually
			glBindVertexArray(spriteRenderer.vao);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
};
