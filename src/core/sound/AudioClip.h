#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "dr_libs/dr_wav.h"

class AudioClip
{
public:
	AudioClip(std::string soundFilName);

	std::uint8_t GetChannels();

	std::uint32_t GetSampleRate();

	std::vector<std::int16_t> GetAudioData();

	std::uint64_t GetTotalSamples();

	bool isStereoAudioClip();

private:
	std::uint32_t channels;

	std::uint32_t sampleRate;

	std::uint64_t totalPcmFrameCount;

	std::vector<std::int16_t> audioData;
};
