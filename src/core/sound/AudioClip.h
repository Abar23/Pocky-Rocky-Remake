#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "OpenAL/al.h"
#include "dr_libs/dr_wav.h"

class AudioClip
{
public:
	AudioClip(std::string pathToFile);

	const std::uint8_t& GetChannels() const;

	const std::uint32_t& GetSampleRate() const;

	const std::vector<char>& GetAudioData() const;

	const std::uint64_t& GetTotalSamples() const;

	const ALenum& GetFormat() const;

	const float& GetClipLengthInMillis() const;

	std::uint8_t& GetChannels();

	std::uint32_t& GetSampleRate();

	std::vector<char>& GetAudioData();

	std::uint64_t& GetTotalSamples();

	ALenum& GetFormat();

	float& GetClipLengthInMillis();

	bool IsStereoAudioClip();

protected:
	std::uint32_t channels;

	std::uint32_t sampleRate;

	std::uint64_t totalPcmFrameCount;

	std::vector<char> audioData;

	float lengthOfClipInMillis;

	ALenum format;
};
