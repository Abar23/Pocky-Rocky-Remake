#pragma once

#include <set>
#include "EcsTypes.h"

class AbstractSystem
{
public:
	std::set<Entity> entities;
};