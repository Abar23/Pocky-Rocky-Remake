#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>
#include "AbstractSystem.h"

class SystemManager
{
public:
	template <typename System>
	std::shared_ptr<System> RegisterSystem();

	template <typename System>
	void SetSignature(Signature signature);

	inline void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : systemsMap)
		{
			pair.second->entities.erase(entity);
		}
	}

	inline void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : systemsMap)
		{
			if ((entitySignature & signaturesMap[pair.first]) == signaturesMap[pair.first])
			{
				pair.second->entities.insert(entity);
			}
			else
			{
				pair.second->entities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> signaturesMap;

	std::unordered_map<const char*, std::shared_ptr<AbstractSystem>> systemsMap;

};

#include "SystemManager.inl"
