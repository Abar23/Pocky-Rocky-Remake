#include <chrono>
#include <iostream>
#include "locators/EcsLocator.h"
#include "core/ecs/framework/EcsManager.h"
#include "core/ecs/components/Gravity.h"
#include "core/ecs/components/Transform.h"
#include "core/ecs/components/RigidBody.h"
#include "core/ecs/systems/PhysicsSystem.h"
#include "core/ecs/framework/EcsTypes.h"
#include "math/Vec3.h"
#include "game.h"
#include <memory>
#include "core/sound/Audio.h"
#include "core/utility/AlErrorCheck.h"

int main()
{

	Game pockyAndRocky;
	pockyAndRocky.run();
	pockyAndRocky.shutdown();

	return 0;
}
