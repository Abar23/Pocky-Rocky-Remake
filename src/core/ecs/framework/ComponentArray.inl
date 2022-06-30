#pragma once

#include "Assert.h"

template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component)
{
	ASSERT(entityToIndexMap.find(entity) == entityToIndexMap.end(), "Entity " << entity << " already added to component array.");
	
	std::uint32_t index = size;
	entityToIndexMap[entity] = index;
	indexToEntityMap[index] = entity;
	componentArray[index] = component;
	size++;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity)
{
	ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end(), "Entity " << entity << " does not exist in component array.");

	std::uint32_t indexOfLastComponent = size - 1;
	std::uint32_t indexOfEntityToRemove = entityToIndexMap[entity];
	componentArray[indexOfEntityToRemove] = componentArray[indexOfLastComponent];

	Entity entityOfLastComponent = indexToEntityMap[indexOfLastComponent];
	entityToIndexMap[entityOfLastComponent] = indexOfEntityToRemove;
	indexToEntityMap[indexOfEntityToRemove] = entityOfLastComponent;

	entityToIndexMap.erase(entity);
	indexToEntityMap.erase(indexOfEntityToRemove);
	size--;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity)
{
	ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end(), "Entity " << entity << " does not exist in component array.");

	return componentArray[indexToEntityMap[entity]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity)
{
	if (entityToIndexMap.find(entity) != entityToIndexMap.end())
	{
		RemoveData(entity);
	}
}
