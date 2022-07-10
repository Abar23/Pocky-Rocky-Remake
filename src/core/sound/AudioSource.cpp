#include <algorithm>
#include "AudioSource.h"
#include "core/utility/AlErrorCheck.h"

#define MAX_GAIN 5.0f
#define MIN_GAIN 1.0f

AudioSource::AudioSource(AudioClip& audioClip) :
	audioClip(audioClip)
{
    // Set default settings
    alCall(alGenSources, 1, &source);
    alCall(alSourcef, source, AL_PITCH, 1);
    alCall(alSourcef, source, AL_GAIN, 1.0f);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
    alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
}

AudioSource::~AudioSource()
{
    alCall(alDeleteSources, 1, &source);
}

void AudioSource::Play()
{
    alCall(alSourcePlay, source);
}

void AudioSource::Pause()
{
    alCall(alSourceStop, source);
}

bool AudioSource::IsPlaying()
{
    ALint isPlaying;
    alCall(alGetSourcei, source, AL_SOURCE_STATE, &isPlaying);
    return (isPlaying == AL_PLAYING);
}

void AudioSource::SetPosition(const vec3& position)
{
    alCall(alSource3f, AL_POSITION, source, position.x, position.y, position.z);
}

vec3 AudioSource::GetPosition()
{
    vec3 currentPosition;
    alCall(alGetSource3f, source, AL_POSITION, &currentPosition.x, &currentPosition.y, &currentPosition.z);
    return currentPosition;
}

void AudioSource::SetPitch(const float pitch)
{
    alCall(alSourcef, source, AL_PITCH, pitch);
}

float AudioSource::SetPitch()
{
    float pitch;
    alCall(alGetSourcef, source, AL_PITCH, &pitch);
    return pitch;
}

void AudioSource::SetGain(const float gain)
{
    float clampedGain = std::clamp(gain, MIN_GAIN, MAX_GAIN);
    alCall(alSourcef, source, AL_GAIN, clampedGain);
}

float AudioSource::GetGain()
{
    float gain;
    alCall(alGetSourcef, source, AL_GAIN, &gain);
    return gain;
}

void AudioSource::SetVelocity(const vec3& velocity)
{
    alCall(alSource3f, source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

vec3 AudioSource::GetVelocity()
{
    vec3 currentVelocity;
    alCall(alGetSource3f, source, AL_POSITION, &currentVelocity.x, &currentVelocity.y, &currentVelocity.z);
    return currentVelocity;
}
