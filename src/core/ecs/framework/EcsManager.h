#pragma once

#include <memory>
#include <iostream>
#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

class EcsManager
{
public: 
	EcsManager()
	{
		systemManager = std::make_unique<SystemManager>();
		entityManager = std::make_unique<EntityManager>();
		componentManager = std::make_unique<ComponentManager>();
	}

	Entity CreateEntity()
	{
		return entityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		entityManager->DestroyEntity(entity);
		systemManager->EntityDestroyed(entity);
		componentManager->EntityDestroyed(entity);
	}

	template<typename T>
	void RegisterComponent();

	template<typename T>
	void AddComponent(Entity entity, T component);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T& GetComponent(Entity entity);

	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemSignature(Signature signature);

private:
	std::unique_ptr<SystemManager> systemManager;

	std::unique_ptr<EntityManager> entityManager;

	std::unique_ptr<ComponentManager> componentManager;

};

#include "EcsManager.inl"
