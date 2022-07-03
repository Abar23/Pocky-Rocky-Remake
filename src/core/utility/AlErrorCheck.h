#pragma once

#include <utility>
#include <iostream>
#include "glad/glad.h"
#include "OpenAL/al.h"
#include "OpenAL/alc.h"

#ifdef DEBUG
	#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
	#define alcCall(function, returnType, device, ...) alcCallImpl(__FILE__, __LINE__, function, returnType, device, __VA_ARGS__)
#else
	#define alCall(function, ...) function(__VA_ARGS__)
	#define alcCall(function, context, device, ...) function(device, __VA_ARGS__)
#endif

// al.h fucntion call error checker

bool checkOpenAlError(const std::string& filename, const std::uint32_t line);


template<typename AlFunction, typename ReturnType, typename... Params>
auto alCallImpl(const char* filename,
	const std::uint32_t line,
	AlFunction function,
	ReturnType& returnType,
	Params&&... params)
	->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
{
	returnType = function(std::forward<Params>(params)...);
	return checkOpenAlError(filename, line);
}

template<typename AlFunction, typename... Params>
auto alCallImpl(const char* filename,
	const std::uint32_t line,
	AlFunction function,
	Params&&... params)
	->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
	function(std::forward<Params>(params)...);
	return checkOpenAlError(filename, line);
}

// alc.h function call error checker

bool checkOpenAlContextError(const std::string& filename, const std::uint32_t line, ALCdevice* device);

template<typename AlContextFunction, typename... Params>
auto alcCallImpl(const char* filename,
	const std::uint32_t line,
	AlContextFunction function,
	ALCdevice* device,
	Params&&... params)
	->typename std::enable_if_t<std::is_same_v<void, decltype(function(device, params...))>, bool>
{
	function(std::forward<Params>(params)...);
	return checkOpenAlContextError(filename, line, device);
}

template<typename AlContextFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename,
	const std::uint32_t line,
	AlContextFunction function,
	ReturnType& returnType,
	ALCdevice* device,
	Params&&... params)
	->typename std::enable_if_t<!std::is_same_v<void, decltype(function(device, params...))>, bool>
{
	returnType = function(device, std::forward<Params>(params)...);
	return checkOpenAlContextError(filename, line, device);
}