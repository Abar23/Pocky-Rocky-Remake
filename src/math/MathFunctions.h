#pragma once

#include <cstdint>
#include <cstring>
#include "MathConstants.h"


template <typename T>
inline bool NearEquals(const T floatOne, const T floatTwo)
{
	T absDiff = std::abs(floatOne - floatTwo);
	if (absDiff <= maxEpsilonDiff)
	{
		return true;
	}

	return false;
}

template <typename T>
inline T DegreesToRad(const T angleInDegrees)
{
	return angleInDegrees * static_cast<T>(F_PI / 180.0f);
}

template <typename T>
inline T RadToDegrees(const T angleInDegrees)
{
	return angleInDegrees * static_cast<T>(180.0f / F_PI);
}

template <typename T>
inline T FastInverseSqurRootAroundOne(const T value)
{
	constexpr T coeffOne = static_cast<T>(15.0f / 8.0f);
	constexpr T coeffTwo = static_cast<T>(-5.0f / 4.0f);
	constexpr T coeffThree = static_cast<T>(3.0f / 8.0f);

	return coeffOne + coeffTwo * value + coeffThree * value * value;
}
