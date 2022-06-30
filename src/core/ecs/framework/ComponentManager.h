#pragma once

#include <unordered_map>
#include <memory>
#include "EcsTypes.h"
#include "IComponentArray.h"
#include "ComponentArray.h"

class ComponentManager
{
public:
	template<typename Component>
	void RegisterComponent();

	template<typename Component>
	ComponentType GetComponentType();

	template<typename Component>
	void AddComponent(Entity entity, Component component);

	template<typename Component>
	void RemoveComponent(Entity entity);

	template<typename Component>
	Component& GetComponent(Entity entity);

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : componentArraysMap)
		{
			pair.second->EntityDestroyed(entity);
		}
	}

private:
	template<typename Component>
	std::shared_ptr<ComponentArray<Component>> GetComponentArray();

	std::unordered_map<const char*, ComponentType> componentTypesMap;

	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArraysMap;

	ComponentType nextComponentTypeId;
};

#include "ComponentManager.inl"
