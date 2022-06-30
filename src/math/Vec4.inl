#pragma once

#include <assert.h>
#include <cmath>
#include "MathFunctions.h"
#include "MathConstants.h"

template <typename T>
Vec4<T>::Vec4()
	: x(0), y(0), z(0), w(0)
{
}

template <typename T>
Vec4<T>::Vec4(const Vec4<T>& vector)
	: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}

template<typename T>
Vec4<T>::Vec4(std::initializer_list<T> args)
{
	int index = 0;
	for (auto begin = args.begin(); begin != args.end(); ++begin)
	{
		this->data.at(index++) = *begin;
	}
}

template <typename T>
Vec4<T>::Vec4(const T x, const T y, const T z, const T w)
	: x(x), y(y), z(z), w(w)
{
}

template <typename T>
Vec4<T>::Vec4(const T x, const T y, const T z)
	: x(x), y(y), z(z), w(0)
{
}

template <typename T>
Vec4<T>::Vec4(const T scalar)
	: x(scalar), y(scalar), z(scalar), w(scalar)
{
}

template <typename T>
T Vec4<T>::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

template <typename T>
T Vec4<T>::SqrMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

template <typename T>
Vec4<T> Vec4<T>::Normalized() const
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));

	T magnitude = Magnitude();

	return Vec4<T>(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
}

template <typename T>
Vec4<T>& Vec4<T>::Normalize()
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));

	*this /= Magnitude();

	return *this;
}

template <typename T>
Vec4<T> Vec4<T>::Renormalized() const
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return Vec4<T>(x * inverseMagnitude, y * inverseMagnitude, z * inverseMagnitude, w * inverseMagnitude);
}

template <typename T>
Vec4<T>& Vec4<T>::Renormalize()
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return *this *= inverseMagnitude;
}

template <typename T>
Vec4<T> Vec4<T>::Negated() const
{
	return *this * static_cast<T>(-1);
}

template <typename T>
Vec4<T>& Vec4<T>::Negate()
{
	*this *= static_cast<T>(-1);
	return *this;
}

template <typename T>
T Vec4<T>::Dot(const Vec4<T>& leftVector, const Vec4<T>& rightVector)
{
	return leftVector.x * rightVector.x + 
			leftVector.y * rightVector.y + 
			leftVector.z * rightVector.z + 
			leftVector.w * rightVector.w;
}

template <typename T>
Vec4<T> Vec4<T>::Lerp(const Vec4<T>& leftVector, const Vec4<T>& rightVector, const T t)
{
	return leftVector * (static_cast<T>(1) - t) + rightVector * t;
}

template <typename T>
Vec4<T> Vec4<T>::Zero()
{
	return Vec4<T>();
}

template <typename T>
Vec4<T>& Vec4<T>::operator=(const Vec4<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

template <typename T>
Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

template <typename T>
Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

template <typename T>
Vec4<T>& Vec4<T>::operator*=(const T scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

template <typename T>
Vec4<T>& Vec4<T>::operator/=(const T scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}
