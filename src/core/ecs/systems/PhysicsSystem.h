#pragma once

#include "core/ecs/components/Gravity.h"
#include "core/ecs/components/Transform.h"
#include "core/ecs/components/RigidBody.h"
#include "core/ecs/framework/AbstractSystem.h"
#include "locators/EcsLocator.h"

class PhysicsSystem : public AbstractSystem
{
public:
	void Update(float dt)
	{
		EcsManager* ecsManager = EcsLocator::GetEcsManager();
		for (auto const& entity : entities)
		{
			auto& rigidBody = ecsManager->GetComponent<RigidBody>(entity);
			auto& transform = ecsManager->GetComponent<Transform>(entity);
			auto const& gravity = ecsManager->GetComponent<Gravity>(entity);

			transform.position += rigidBody.velocity * dt;

			rigidBody.velocity += gravity.force * dt;
		}
	}
};

