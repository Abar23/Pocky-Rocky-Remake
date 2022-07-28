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
			glCall(glActiveTexture, GL_TEXTURE0);
			glCall(glBindTexture, GL_TEXTURE_2D, spriteRenderer.textureID);
			spriteRenderer.shader->setInt("entityTexture", 0);
			int currentRow = spriteRenderer.currentFrame / spriteRenderer.columns;
			int currentColumn = spriteRenderer.currentFrame % spriteRenderer.columns;
			glUniform2f(
				glGetUniformLocation(spriteRenderer.shader->ID, "FrameOffset"), 
				currentColumn * spriteRenderer.frameWidth,
				-currentRow * spriteRenderer.frameHeight);

			// camera stuff
			spriteRenderer.shader->setVec3("camPos", &spriteRenderer.cameraPosition.data[0]);

			spriteRenderer.shader->setVec2("entityPos", &transform.position.data[0]);

			glBindVertexArray(spriteRenderer.vao);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
};
