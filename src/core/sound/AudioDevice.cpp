#include "AudioDevice.h"
#include "core/utility/AlErrorCheck.h"

AudioDevice::AudioDevice()
{
	audioDevice = alcOpenDevice(nullptr);
	if (audioDevice != nullptr) {
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "OpenAL failed to open default device!" << std::endl;
		std::terminate();
	}

	if (!alcCall(alcCreateContext, audioContext, audioDevice, nullptr))
	{

	}
}

AudioDevice::~AudioDevice()
{
}
