#pragma once

#include "AudioSource.h"
#include "AudioClip.h"

class EffectAudioSource : public AudioSource
{
public:
	EffectAudioSource(AudioClip& audioClip);

	virtual ~EffectAudioSource();

	void SetLooping(const bool loop) override;

	void Update() override;

private:
	ALuint buffer;
};

