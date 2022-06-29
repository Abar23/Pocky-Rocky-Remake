#pragma once

template<typename T>
void EcsManager::RegisterComponent()
{
	componentManager->RegisterComponent<T>();
}

template<typename T>
void EcsManager::AddComponent(Entity entity, T component)
{
	componentManager->AddComponent<T>(entity, component);

	Signature signature = entityManager->GetSignature(entity);
	signature.set(componentManager->GetComponentType<T>(), true);
	entityManager->SetSignature(entity, signature);

	systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void EcsManager::RemoveComponent(Entity entity)
{
	componentManager->RemoveComponent<T>(entity);

	Signature signature = entityManager->GetSignature(entity);
	signature.set(componentManager->GetComponentType<T>(), false);
	entityManager->SetSignature(signature);

	systemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& EcsManager::GetComponent(Entity entity)
{
	return componentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType EcsManager::GetComponentType()
{
	return componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> EcsManager::RegisterSystem()
{
	return systemManager->RegisterSystem<T>();
}

template<typename T>
 void EcsManager::SetSystemSignature(Signature signature)
{
	systemManager->SetSignature<T>(signature);
}
