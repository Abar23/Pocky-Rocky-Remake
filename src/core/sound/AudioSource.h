#pragma once

#include <thread>
#include <vector>
#include "OpenAL/al.h"
#include "AudioClip.h"
#include "math/Vec3.h"
#include "AudioConstants.h"

class AudioSource
{
public:
	AudioSource();

	AudioSource(const float pitch,
				const float gain,
				const vec3& position,
				const vec3& velocity,
				const bool loop);

	virtual ~AudioSource();

	void Play(AudioClip& audioClip);

	void Pause();

	void Stop();

	void Mute();

	void Unmute();

	bool IsPlaying();

	bool IsPaused();

	bool IsStopped();

	void SetPosition(const vec3& position);

	vec3 GetPosition();

	void SetPitch(const float pitch);

	float SetPitch();

	void SetGain(const float gain);

	float GetGain();

	void SetVelocity(const vec3& velocity);

	vec3 GetVelocity();
	
	void SetLooping(bool loop);

protected:
	ALuint source;

	float previousGain;

	std::thread* streamingThread;

	bool isStreaming;

	bool isLooping;

	std::uint64_t cursor;

	std::vector<ALuint> bufferIds;

	void PlayStream(const AudioClip& audioClip);

	void UpdateBuffers(const AudioClip& audioClip);
};

