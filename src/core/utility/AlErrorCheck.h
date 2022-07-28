#pragma once

#include <utility>
#include <iostream>
#include "glad/glad.h"
#include "OpenAL/al.h"
#include "OpenAL/alc.h"

#ifdef DEBUG
	#define alCall(func, ...) \
	func(__VA_ARGS__); \
	checkOpenAlError(__FILE__, __LINE__);

	#define alcCall(func, device, ...) \
	func(__VA_ARGS__); \
	checkOpenAlContextError(__FILE__, __LINE__, device);
#else
	#define alCall(func, ...) func(__VA_ARGS__); 

	#define alcCall(func, device, ...) func(__VA_ARGS__); 
#endif

// al.h fucntion call error checker
bool checkOpenAlError(const std::string& filename, const std::uint32_t line);

// alc.h function call error checker
bool checkOpenAlContextError(const std::string& filename, const std::uint32_t line, ALCdevice* device);