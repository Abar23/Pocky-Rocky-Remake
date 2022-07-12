#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include "AudioSource.h"
#include "core/utility/AlErrorCheck.h"

#define MAX_GAIN 5.0f
#define MIN_GAIN 0.0f

AudioSource::AudioSource()
{
    // Set default settings
    alCall(alGenSources, 1, &source);
    alCall(alSourcef, source, AL_PITCH, 1);
    alCall(alSourcef, source, AL_GAIN, 1.0f);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
    alCall(alSourcei, source, AL_LOOPING, AL_FALSE);

    ALuint bufferId;
    alCall(alGenBuffers, 1, &bufferId);
    bufferIds.push_back(bufferId);

    previousGain = 1.0f;
    isLooping = false;
    isStreaming = false;
    streamingThread = nullptr;
    cursor = 0;
}

AudioSource::AudioSource(const float pitch, 
                         const float gain, 
                         const vec3& position, 
                         const vec3& velocity,
                         const bool loop)
{
    alCall(alGenSources, 1, &source);

    SetGain(gain);
    SetPitch(pitch);
    SetPosition(position);
    SetVelocity(velocity);
    SetLooping(loop);
    
    ALuint bufferId;
    alCall(alGenBuffers, 1, &bufferId);
    bufferIds.push_back(bufferId);

    previousGain = gain;
    isStreaming = false;
    streamingThread = nullptr;
    cursor = 0;
}

AudioSource::~AudioSource()
{
    alCall(alSourceStop, source);
    if (streamingThread != nullptr && streamingThread->joinable())
    {
        streamingThread->join();
        delete streamingThread;
    }
    alCall(alSourcei, source, AL_BUFFER, 0);
    alCall(alDeleteBuffers, bufferIds.size(), &bufferIds[0]);
    alCall(alDeleteSources, 1, &source);
}

void AudioSource::Play(AudioClip& audioClip)
{
    alCall(alSourceStop, source);

    if (streamingThread != nullptr && streamingThread->joinable())
    {
        streamingThread->join();
        delete streamingThread;
    }

    alCall(alSourcei, source, AL_BUFFER, 0);
    const auto& audioData = audioClip.GetAudioData();
    std::uint64_t audioDataUnitSize = sizeof(audioData[0]);
    if (audioData.size() * audioDataUnitSize <= BUFFER_SIZE)
    {
        alCall(alSourcei, source, AL_LOOPING, (ALint)isLooping);

        alCall(alBufferData,
            bufferIds[0],
            audioClip.GetFormat(),
            audioData.data(),
            audioData.size() * audioDataUnitSize,
            audioClip.GetSampleRate());
        alCall(alSourcei, source, AL_BUFFER, bufferIds[0]);

        isStreaming = false;
    }
    else
    {
        alCall(alSourcei, source, AL_LOOPING, (ALint)false);

        if (bufferIds.size() < MAX_BUFFERS)
        {
            bufferIds.resize(MAX_BUFFERS);
            alCall(alGenBuffers, 3, &bufferIds[1]);
        }

        cursor = 0;

        for (int i = 0; i < MAX_BUFFERS; i++)
        {
            const char* data = nullptr;
            std::uint64_t dataSize = 0;

            if (i * BUFFER_SIZE < audioData.size())
            {
                data = &audioData[i * BUFFER_SIZE];

                std::uint64_t sizeOfDataToCopy = BUFFER_SIZE;
                if (cursor + BUFFER_SIZE > audioData.size() * audioDataUnitSize)
                {
                    sizeOfDataToCopy = audioData.size() * audioDataUnitSize - cursor;
                }
                dataSize = sizeOfDataToCopy;
            }

            alCall(alBufferData,
                bufferIds[i],
                audioClip.GetFormat(),
                data,
                dataSize,
                audioClip.GetSampleRate());

            cursor += dataSize;
        }

        alCall(alSourceQueueBuffers, source, MAX_BUFFERS, &bufferIds[0]);
        
        isStreaming = true;
    }
    alCall(alSourcePlay, source);

    if (isStreaming)
    {
        streamingThread = new std::thread(&AudioSource::PlayStream, this, audioClip);
    }
}

void AudioSource::Pause()
{
    alCall(alSourcePause, source);
}

void AudioSource::Stop()
{
    alCall(alSourceStop, source);
}

void AudioSource::Mute()
{
    alCall(alGetSourcef, source, AL_GAIN, &previousGain)
    SetGain(0.0f);
}

void AudioSource::Unmute()
{
    if (GetGain() == 0.0f)
    {
        SetGain(previousGain);
    }
}

bool AudioSource::IsPlaying()
{
    ALint isPlaying;
    alCall(alGetSourcei, source, AL_SOURCE_STATE, &isPlaying);
    return (isPlaying == AL_PLAYING);
}

bool AudioSource::IsPaused()
{
    ALint isPlaying;
    alCall(alGetSourcei, source, AL_SOURCE_STATE, &isPlaying);
    return (isPlaying == AL_PAUSED);
}

bool AudioSource::IsStopped()
{
    ALint isPlaying;
    alCall(alGetSourcei, source, AL_SOURCE_STATE, &isPlaying);
    return (isPlaying == AL_STOPPED);
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

void AudioSource::SetLooping(bool loop)
{
    isLooping = loop;

    if (!isStreaming)
    {
        alCall(alSourcei, source, AL_LOOPING, (ALint)isLooping);
    }
}

void AudioSource::PlayStream(const AudioClip& audioClip)
{
    while (!IsStopped())
    {
        UpdateBuffers(std::forward<const AudioClip>(audioClip));
    }
}

void AudioSource::UpdateBuffers(const AudioClip& audioClip)
{
    ALint buffersProcessed;
    alCall(alGetSourcei, source, AL_BUFFERS_PROCESSED, &buffersProcessed);
    const std::vector<char>& audioData = audioClip.GetAudioData();
    while (buffersProcessed && cursor < audioData.size())
    {
        ALuint buffer;
        alCall(alSourceUnqueueBuffers, source, 1, &buffer);
    
        char* data = (char*)std::calloc(BUFFER_SIZE, sizeof(audioData[0]));
    
        std::uint64_t sizeOfDataToCopy = BUFFER_SIZE;
        if (cursor + BUFFER_SIZE > audioData.size())
        {
    	    sizeOfDataToCopy = audioData.size() * sizeof(audioData[0]) - cursor;
        }
    
        std::memcpy(data, &audioData[cursor], sizeOfDataToCopy);
        cursor += sizeOfDataToCopy;

        if (isLooping && sizeOfDataToCopy < BUFFER_SIZE)
        {
    	    std::memcpy(&data[sizeOfDataToCopy], &audioData[0], (BUFFER_SIZE - sizeOfDataToCopy));
    	    cursor = BUFFER_SIZE - sizeOfDataToCopy;
        }
    
        alCall(alBufferData, buffer, audioClip.GetFormat(), data, BUFFER_SIZE, audioClip.GetSampleRate());
        alCall(alSourceQueueBuffers, source, 1, &buffer);
    
        std::free(data);
    
        buffersProcessed--;
    }
}
