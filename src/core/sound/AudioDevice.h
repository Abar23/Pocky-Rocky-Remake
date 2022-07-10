#pragma once

#include <array>
#include "OpenAL/al.h"
#include "OpenAL/alc.h"
#include "math/Vec3.h"

class AudioDevice
{
public: 
	AudioDevice();

	~AudioDevice();

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
	ALCdevice* audioDevice;

	ALCcontext* audioContext;

	int attenutationDistanceModel;
};

