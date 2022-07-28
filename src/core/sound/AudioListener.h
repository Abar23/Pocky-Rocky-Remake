#pragma once

#include "math/Vec3.h"

class AudioListener
{
public:
	AudioListener();

	AudioListener(const int distanceModel,
				  const float gain,
				  const vec3& position,
				  const vec3& velocity,
				  const vec3& upVector,
				  const vec3& forwardVector);

	void SetAttenuation(const int distanceModel);

	int GetAttenuation();

	void SetGain(const float gain);

	float GetGain();

	void SetPosition(const vec3& position);

	vec3 GetPosition();

	void SetOrientation(const vec3& at, const vec3& up);

	std::array<vec3, 2> GetOrientation();

	void SetVelocity(const vec3& velocity);

	vec3 GetVelocity();

private:
	int attenutationDistanceModel;
};

