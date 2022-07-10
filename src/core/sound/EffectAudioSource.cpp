#include <vector>
#include <cstdint>
#include "EffectAudioSource.h"
#include "core/utility/AlErrorCheck.h"

EffectAudioSource::EffectAudioSource(AudioClip& audioClip) :
	AudioSource(audioClip)
{
	std::vector<std::int16_t> audioData = audioClip.GetAudioData();
	alCall(alGenBuffers, 1, &buffer);
	alCall(alBufferData,
		   buffer,
		   (audioClip.GetChannels() > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
		   audioData.data(),
		   audioData.size() * sizeof(audioData[0]),
		   audioClip.GetSampleRate());
	alCall(alSourcei, source, AL_BUFFER, buffer);
}

EffectAudioSource::~EffectAudioSource()
{
	//Must unbond the buffer from the source to delete the buffer
	alCall(alSourceStop, source);
	alCall(alSourcei, source, AL_BUFFER, 0); 
	alCall(alDeleteBuffers, 1, &buffer);
}

void EffectAudioSource::SetLooping(const bool loop)
{
	alCall(alSourcei, source, AL_LOOPING, (ALint)loop);
}

void EffectAudioSource::Update()
{
}
