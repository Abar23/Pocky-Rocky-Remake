#include <algorithm>
#include "AudioListener.h"
#include "OpenAL/al.h"
#include "core/utility/Assert.h"
#include "core/utility/AlErrorCheck.h"
#include "AudioConstants.h"

AudioListener::AudioListener()
{
	// Set default settings
	alCall(alListenerf, AL_GAIN, 1.0f);
	alCall(alListener3f, AL_POSITION, 0, 0, 0);
	alCall(alListener3f, AL_VELOCITY, 0, 0, 0);
	ALfloat forwardAndUpVectors[6] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	alCall(alListenerfv, AL_ORIENTATION, forwardAndUpVectors);
	SetAttenuation(AL_NONE);

}

AudioListener::AudioListener(const int distanceModel, 
							 const float gain, 
							 const vec3& position, 
							 const vec3& velocity, 
							 const vec3& upVector, 
							 const vec3& forwardVector)
{
	SetGain(gain);
	SetPosition(position);
	SetVelocity(velocity);
	SetAttenuation(distanceModel);
	SetOrientation(forwardVector, upVector);
}

void AudioListener::SetAttenuation(const int distanceModel)
{
	ASSERT(distanceModel >= AL_INVERSE_DISTANCE && distanceModel <= AL_EXPONENT_DISTANCE_CLAMPED, "Invalid distance model for listener attentuation!");

	alCall(alDistanceModel, distanceModel);
}

int AudioListener::GetAttenuation()
{
	return attenutationDistanceModel;
}

void AudioListener::SetGain(const float gain)
{
	float clampedGain = std::clamp(gain, MIN_GAIN, MAX_GAIN);
	alCall(alListenerf, AL_GAIN, clampedGain);
}

float AudioListener::GetGain()
{
	float currentGain;
	alCall(alGetListenerf, AL_GAIN, &currentGain);
	return currentGain;
}

void AudioListener::SetPosition(const vec3& position)
{
	alCall(alListener3f, AL_POSITION, position.x, position.y, position.z);
}

vec3 AudioListener::GetPosition()
{
	vec3 currentPosition;
	alCall(alGetListener3f, AL_POSITION, &currentPosition.x, &currentPosition.y, &currentPosition.z);
	return currentPosition;
}

void AudioListener::SetOrientation(const vec3& at, const vec3& up)
{
	ALfloat values[6] = { at.x, at.y, at.z, up.x, up.y, up.z };
	alCall(alListenerfv, AL_ORIENTATION, values);
}

std::array<vec3, 2> AudioListener::GetOrientation()
{
	ALfloat values[6];
	alCall(alGetListenerfv, AL_ORIENTATION, values);

	std::array<vec3, 2> orientationVectors;
	orientationVectors[0] = vec3(values[0], values[1], values[2]);
	orientationVectors[1] = vec3(values[2], values[3], values[5]);

	return orientationVectors;
}

void AudioListener::SetVelocity(const vec3& velocity)
{
	alCall(alListener3f, AL_POSITION, velocity.x, velocity.y, velocity.z);
}

vec3 AudioListener::GetVelocity()
{
	vec3 velocity;
	alCall(alGetListener3f, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
