#pragma once

#include "core/utility/Assert.h"

template<typename System>
std::shared_ptr<System> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(System).name();

	ASSERT(systemsMap.find(typeName) == systemsMap.end(), "System already registered. System type name is " << typeName);

	auto system = std::make_shared<System>();
	systemsMap.insert({ typeName, system });
	return system;
}

template<typename System>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(System).name();

	ASSERT(systemsMap.find(typeName) != systemsMap.end(), "System not registered. System type name is " << typeName);

	signaturesMap.insert({ typeName, signature });
}

