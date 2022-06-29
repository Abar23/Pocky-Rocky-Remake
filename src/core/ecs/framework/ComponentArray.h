#pragma once

#include <array>
#include <unordered_map>
#include "IComponentArray.h"

template <typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component);

	void RemoveData(Entity entity);

	T& GetData(Entity entity);

	void EntityDestroyed(Entity entity) override;

private:
	std::array<T, MAX_ENTITIES> componentArray;

	std::unordered_map<Entity, std::uint32_t> entityToIndexMap;

	std::unordered_map<std::uint32_t, uint32_t> indexToEntityMap;

	std::uint32_t size;
};

#include "ComponentArray.inl"
