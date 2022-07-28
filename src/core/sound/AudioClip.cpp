#include <iostream>
#include <memory>
#include "AudioClip.h"

AudioClip::AudioClip(std::string pathToFile)
{
	char* sampleData = (char*)drwav_open_file_and_read_pcm_frames_s16(pathToFile.c_str(), &channels, &sampleRate, &totalPcmFrameCount, nullptr);
	
	if (sampleData == nullptr)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Failed to load wav file using drwav!" << std::endl;
		std::terminate();
	}
	audioData.resize(GetTotalSamples() * sizeof(std::int16_t));
	std::memcpy(audioData.data(), sampleData, audioData.size());
	drwav_free(sampleData, nullptr);
	
	format = (channels > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

	lengthOfClipInMillis = (float)totalPcmFrameCount / (float)sampleRate * 1000.0f;
}

std::uint8_t& AudioClip::GetChannels()
{
	return const_cast<std::uint8_t&>(const_cast<const AudioClip*>(this)->GetChannels());
}

const std::uint8_t& AudioClip::GetChannels() const
{
	return channels;
}

std::uint32_t& AudioClip::GetSampleRate()
{
	return const_cast<std::uint32_t&>(const_cast<const AudioClip*>(this)->GetSampleRate());
}

const std::uint32_t& AudioClip::GetSampleRate() const
{
	return sampleRate;
}

std::vector<char>& AudioClip::GetAudioData()
{
	return const_cast<std::vector<char>&>(const_cast<const AudioClip*>(this)->GetAudioData());
}

const std::vector<char>& AudioClip::GetAudioData() const
{
	return audioData;
}

std::uint64_t& AudioClip::GetTotalSamples()
{
	return const_cast<std::uint64_t&>(const_cast<const AudioClip*>(this)->GetTotalSamples());
}

const std::uint64_t& AudioClip::GetTotalSamples() const
{
	return totalPcmFrameCount * channels;
}

ALenum& AudioClip::GetFormat()
{
	return const_cast<ALenum&>(const_cast<const AudioClip*>(this)->GetFormat());
}

const ALenum& AudioClip::GetFormat() const
{
	return format;
}

float& AudioClip::GetClipLengthInMillis()
{
	return const_cast<float&>(const_cast<const AudioClip*>(this)->GetClipLengthInMillis());
}

const float& AudioClip::GetClipLengthInMillis() const
{
	return lengthOfClipInMillis;
}

bool AudioClip::IsStereoAudioClip()
{
	return (channels == 1) ? false : true;
}
