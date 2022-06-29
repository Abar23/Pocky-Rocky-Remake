#pragma once

#include <queue>
#include <array>
#include "EcsTypes.h"
#include "Assert.h"

class EntityManager
{
public:

	EntityManager()
	{
		totalEntitiesAlive = 0;
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
		{
			freeEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		ASSERT(totalEntitiesAlive < MAX_ENTITIES, "Tried to create more entities than allowed. Can only create " << MAX_ENTITIES << " entities.");

		Entity entity = freeEntities.front();
		freeEntities.pop();
		totalEntitiesAlive++;

		return entity;
	}

	void DestroyEntity(Entity entity)
	{
		ASSERT(entity < MAX_ENTITIES, "Tried to destroy invalid entity. Entity id was " << entity);

		entitySignatures[entity].reset();
		freeEntities.push(entity);
		totalEntitiesAlive--;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		ASSERT(entity < MAX_ENTITIES, "Tried set signature of invalid entity. Entity id was " << entity);

		entitySignatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		ASSERT(entity < MAX_ENTITIES, "Tried get signature of invalid entity. Entity id was " << entity);

		return entitySignatures[entity];
	}


private:
	std::queue<Entity> freeEntities;
	
	std::array<Signature, MAX_ENTITIES> entitySignatures;

	std::uint32_t totalEntitiesAlive;

};
