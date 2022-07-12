#pragma once

#include <array>
#include "OpenAL/al.h"
#include "OpenAL/alc.h"
#include "math/Vec3.h"

class AudioDevice
{
public: 
	AudioDevice();

	~AudioDevice();

private:
	ALCdevice* audioDevice;

	ALCcontext* audioContext;
};

