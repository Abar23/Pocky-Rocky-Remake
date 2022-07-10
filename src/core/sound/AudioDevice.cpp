#include <algorithm>
#include "AudioDevice.h"
#include "core/utility/AlErrorCheck.h"
#include "core/utility/Assert.h"

#define MAX_GAIN 5.0f
#define MIN_GAIN 1.0f

AudioDevice::AudioDevice()
{
	const ALCchar* devices;
	devices = alcCall(alcGetString, nullptr, nullptr, ALC_ALL_DEVICES_SPECIFIER);
	audioDevice = alcOpenDevice(devices);
	if (audioDevice == nullptr) {
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "OpenAL failed to open default device!" << std::endl;
		std::terminate();
	}

	audioContext = alcCall(alcCreateContext, audioDevice, audioDevice, nullptr);
	if (audioContext == nullptr)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Filaed to create OpenAL context!" << std::endl;
		std::terminate();
	}

	ALCboolean isContextCurrent = alcCall(alcMakeContextCurrent, audioDevice, audioContext);
	if (!isContextCurrent)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Failed make OpenAL context the current context!" << std::endl;
		std::terminate();
	}

	attenutationDistanceModel = -1;
}

AudioDevice::~AudioDevice()
{
	alcCall(alcMakeContextCurrent, audioDevice, nullptr);
	alcDestroyContext(audioContext);
	alcCloseDevice(audioDevice);
}

void AudioDevice::SetAttenuation(const int distanceModel)
{
	ASSERT(distanceModel >= AL_INVERSE_DISTANCE && distanceModel <= AL_EXPONENT_DISTANCE_CLAMPED, "Invalid distance model for listener attentuation!");

	alCall(alDistanceModel, distanceModel);
	attenutationDistanceModel = distanceModel;
}

int AudioDevice::GetAttenuation()
{
	ASSERT(attenutationDistanceModel != -1, "Attentuation distance model never set!");

	return attenutationDistanceModel;
}

void AudioDevice::SetGain(const float gain)
{
	float clampedGain = std::clamp(gain, MIN_GAIN, MAX_GAIN);
	alCall(alListenerf, AL_GAIN, clampedGain);
}

float AudioDevice::GetGain()
{
	float currentGain;
	alCall(alGetListenerf, AL_GAIN, &currentGain);
	return currentGain;
}

void AudioDevice::SetPosition(const vec3& position)
{
	alCall(alListener3f, AL_POSITION, position.x, position.y, position.z);
}

vec3 AudioDevice::GetPosition()
{
	vec3 currentPosition;
	alCall(alGetListener3f, AL_POSITION, &currentPosition.x, &currentPosition.y, &currentPosition.z);
	return currentPosition;
}

void AudioDevice::SetOrientation(const vec3& at, const vec3& up)
{
	ALfloat values[6] = {at.x, at.y, at.z, up.x, up.y, up.z};
	alCall(alListenerfv, AL_ORIENTATION, values);
}

std::array<vec3, 2> AudioDevice::GetOrientation()
{
	ALfloat values[6];
	alCall(alGetListenerfv, AL_ORIENTATION, values);

	std::array<vec3, 2> orientationVectors;
	orientationVectors[0] = vec3(values[0], values[1], values[2]);
	orientationVectors[1] = vec3(values[2], values[3], values[5]);

	return orientationVectors;
}

void AudioDevice::SetVelocity(const vec3& velocity)
{
	alCall(alListener3f, AL_POSITION, velocity.x, velocity.y, velocity.z);
}

vec3 AudioDevice::GetVelocity()
{
	vec3 velocity;
	alCall(alGetListener3f, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
