#include <iostream>
#include <memory>
#include "AudioClip.h"

AudioClip::AudioClip(std::string soundFileName)
{
	std::int16_t* sampleData = (std::int16_t*)drwav_open_file_and_read_pcm_frames_s16(soundFileName.c_str(), &channels, &sampleRate, &totalPcmFrameCount, nullptr);
	
	if (sampleData == nullptr)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Failed to load wav file using drwav!" << std::endl;
		std::terminate();
	}

	audioData.resize(GetTotalSamples());
	std::memcpy(audioData.data(), sampleData, audioData.size() * sizeof(std::int16_t));
	drwav_free(sampleData, nullptr);
}

std::uint8_t AudioClip::GetChannels()
{
	return channels;
}

std::uint32_t AudioClip::GetSampleRate()
{
	return sampleRate;
}

std::vector<std::int16_t> AudioClip::GetAudioData()
{
	return audioData;
}

std::uint64_t AudioClip::GetTotalSamples()
{
	return totalPcmFrameCount * channels;
}

bool AudioClip::isStereoAudioClip()
{
	return (channels == 1) ? false : true;
}
