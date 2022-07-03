#pragma once

#include "OpenAL/al.h"
#include "OpenAL/alc.h"

class AudioDevice
{
public: 
	AudioDevice();

	~AudioDevice();



private:
	ALCdevice* audioDevice;

	ALCcontext* audioContext;
};

