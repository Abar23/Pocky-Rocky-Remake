#pragma once

#include "OpenAL/al.h"
#include "AudioClip.h"
#include "math/Vec3.h"

class AudioSource
{
public:
	AudioSource(AudioClip& audioClip);

	virtual ~AudioSource();

	void Play();

	void Pause();

	bool IsPlaying();

	void SetPosition(const vec3& position);

	vec3 GetPosition();

	void SetPitch(const float pitch);

	float SetPitch();

	void SetGain(const float gain);

	float GetGain();

	void SetVelocity(const vec3& velocity);

	vec3 GetVelocity();
	
	virtual void SetLooping(bool loop) = 0;

	virtual void Update() = 0;

protected:
	AudioClip audioClip;

	ALuint source;
};

