#pragma once

#include "core/ecs/framework/EcsManager.h"

class EcsLocator 
{
public:
	static EcsManager* GetEcsManager()
	{
		return ecsManagerInstance;
	}

	static void provide(EcsManager* ecsManager)
	{
		ecsManagerInstance = ecsManager;
	}

private:
	inline static EcsManager* ecsManagerInstance;
};