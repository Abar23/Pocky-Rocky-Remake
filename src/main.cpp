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
#include "OpenAL/al.h"
#include "OpenAL/alc.h"
#include "core/utility/Assert.h"
#include "core/utility/ErrorCheck.h"

int main()
{
	ALCdevice* device = nullptr;
	const char* devices = alcCall(alcGetString, device, (ALCdevice*)(0), -1);
	while (devices && *devices != NULL)
	{
		//ALCdevice* device = alcOpenDevice(devices);
		std::cout << devices << std::endl;
		devices += strlen(devices) + 1; //next device
	}
	Game pockyAndRocky;
	pockyAndRocky.run();
	pockyAndRocky.shutdown();

	EcsManager ecsManager;

	EcsLocator::provide(&ecsManager);

	ecsManager.RegisterComponent<Gravity>();
	ecsManager.RegisterComponent<RigidBody>();
	ecsManager.RegisterComponent<Transform>();

	auto physicsSystem = ecsManager.RegisterSystem<PhysicsSystem>();

	Signature signature;
	signature.set(ecsManager.GetComponentType<Gravity>());
	signature.set(ecsManager.GetComponentType<RigidBody>());
	signature.set(ecsManager.GetComponentType<Transform>());
	ecsManager.SetSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	for (auto& entity : entities)
	{
		entity = ecsManager.CreateEntity();

		ecsManager.AddComponent(
			entity,
			Gravity{ vec3(0.0f, -9.8f, 0.0f) });

		ecsManager.AddComponent(
			entity,
			RigidBody{
				.velocity = vec3(0.0f, 100.0f, 0.0f),
				.acceleration = vec3(0.0f, 5.0f, 0.0f)
			});

		ecsManager.AddComponent(
			entity,
			Transform{
				.position = vec3(0.0f, 0.0f, 0.0f),
				.rotation = vec3(0.0f, 0.0f, 0.0f),
				.scale = vec3(1.0f, 1.0f, 1.0f)
			});
	}

	float dt = 0.0f;

	auto startTime = std::chrono::high_resolution_clock::now();

	physicsSystem->Update(1.0f);

	std::cout << ecsManager.GetComponent<Transform>(*physicsSystem->entities.begin()).position;

	auto stopTime = std::chrono::high_resolution_clock::now();

	dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();

	return 0;
}
