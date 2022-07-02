#pragma once

#include "core/utility/Assert.h"

template<typename Component>
void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(Component).name();

	ASSERT(componentTypesMap.find(typeName) == componentTypesMap.end(), "Component already registered. Component type name is " << typeName);

	componentTypesMap.insert({ typeName, nextComponentTypeId });

	componentArraysMap.insert({ typeName, std::make_shared<ComponentArray<Component>>() });

	nextComponentTypeId++;
}

template<typename Component>
ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(Component).name();

	ASSERT(componentTypesMap.find(typeName) != componentTypesMap.end(), "Component is not registered. Component type name is " << typeName);

	return componentTypesMap[typeName];
}

template<typename Component>
void ComponentManager::AddComponent(Entity entity, Component component)
{
	GetComponentArray<Component>()->InsertData(entity, component);
}

template<typename Component>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<Component>()->RemoveData(entity);
}

template<typename Component>
Component& ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<Component>()->GetData(entity);
}

template<typename Component>
std::shared_ptr<ComponentArray<Component>> ComponentManager::GetComponentArray()
{
	const char* typeName = typeid(Component).name();

	ASSERT(componentTypesMap.find(typeName) != componentTypesMap.end(), "Component is not registered. Component is " << typeName);

	return std::static_pointer_cast<ComponentArray<Component>>(componentArraysMap[typeName]);
}
