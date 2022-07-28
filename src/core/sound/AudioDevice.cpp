#include <algorithm>
#include "AudioDevice.h"
#include "core/utility/AlErrorCheck.h"
#include "core/utility/Assert.h"

#define MAX_GAIN 5.0f
#define MIN_GAIN 0.0f

AudioDevice::AudioDevice()
{
	const ALCchar* devices;
	devices = alcCall(alcGetString, nullptr, nullptr, ALC_ALL_DEVICES_SPECIFIER);
	audioDevice = alcOpenDevice(devices);
	if (audioDevice == nullptr) {
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "OpenAL failed to open default device!" << std::endl;
		std::terminate();
	}

	audioContext = alcCall(alcCreateContext, audioDevice, audioDevice, nullptr);
	if (audioContext == nullptr)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Filaed to create OpenAL context!" << std::endl;
		std::terminate();
	}

	ALCboolean isContextCurrent = alcCall(alcMakeContextCurrent, audioDevice, audioContext);
	if (!isContextCurrent)
	{
		std::cerr << "***ERROR*** (" << __FILE__ << ": " << __LINE__ << ")\n";
		std::cerr << "Failed make OpenAL context the current context!" << std::endl;
		std::terminate();
	}
}

AudioDevice::~AudioDevice()
{
	alcCall(alcMakeContextCurrent, audioDevice, nullptr);
	alcCall(alcDestroyContext, audioDevice, audioContext);
	alcCall(alcCloseDevice, audioDevice, audioDevice);
}