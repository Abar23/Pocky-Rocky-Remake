#pragma once

#include <assert.h>
#include <cmath>
#include "MathFunctions.h"
#include "MathConstants.h"

template <typename T>
Vec3<T>::Vec3()
	: x(0), y(0), z(0)
{
}

template<typename T>
Vec3<T>::Vec3(std::initializer_list<T> args)
{
	int index = 0;
	for (auto begin = args.begin(); begin != args.end(); ++begin)
	{
		this->data.at(index++) = *begin;
	}
}

template <typename T>
Vec3<T>::Vec3(const T x, const T y, const T z)
	: x(x), y(y), z(z)
{
}

template <typename T>
Vec3<T>::Vec3(const T value)
	: x(value), y(value), z(value)
{
}

template <typename T>
T Vec3<T>::Magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
T Vec3<T>::SqrMagnitude() const
{
	return x * x + y * y + z * z;
}

template <typename T>
Vec3<T> Vec3<T>::Normalize() const
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));

	T magnitude = Magnitude();

	return Vec2<T>(x / magnitude, y / magnitude);
}

template <typename T>
Vec3<T>& Vec3<T>::Normalized()
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));

	*this /= Magnitude();

	return *this;
}

template <typename T>
Vec3<T> Vec3<T>::Renormalized() const
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return Vec3(x * inverseMagnitude, y * inverseMagnitude, z * inverseMagnitude);
}

template <typename T>
Vec3<T>& Vec3<T>::Renormalize()
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return *this *= inverseMagnitude;
}

template <typename T>
Vec3<T> Vec3<T>::Negated() const
{
	return *this * static_cast<T>(-1);
}

template <typename T>
Vec3<T>& Vec3<T>::Negate()
{
	*this *= static_cast<T>(-1);
	return *this;
}

template <typename T>
T Vec3<T>::Dot(const Vec3& leftVector, const Vec3& rightVector)
{
	return leftVector.x * rightVector.x +
			leftVector.y * rightVector.y +
			leftVector.z * rightVector.z;
}

template <typename T>
Vec3<T> Vec3<T>::Cross(const Vec3& leftVector, const Vec3& rightVector)
{
	return Vec3(leftVector.y * rightVector.z - leftVector.z * rightVector.y,
				leftVector.z * rightVector.x - leftVector.x * rightVector.z,
				leftVector.x * rightVector.y - leftVector.y * rightVector.x);
}

template <typename T>
Vec3<T> Vec3<T>::Project(const Vec3& leftVector, const Vec3& rightVector)
{
	return rightVector * (Dot(leftVector, rightVector) / Dot(rightVector, rightVector));
}

template <typename T>
Vec3<T> Vec3<T>::Reject(const Vec3& leftVector, const Vec3& rightVector)
{
	return leftVector - Project(leftVector, rightVector);
}

template <typename T>
Vec3<T> Vec3<T>::Lerp(const Vec3& leftVector, const Vec3& rightVector, const float t)
{
	return leftVector * (1.0f - t) + rightVector * t;
}

template <typename T>
Vec3<T> Vec3<T>::Zero()
{
	return Vec3<T>(0, 0, 0);
}

template <typename T>
Vec3<T> Vec3<T>::XAxis()
{
	return Vec3<T>(1, 0, 0);
}

template <typename T>
Vec3<T> Vec3<T>::YAxis()
{
	return Vec3<T>(0, 1, 0);
}

template <typename T>
Vec3<T> Vec3<T>::ZAxis()
{
	return Vec3<T>(0, 0, 1);
}

template <typename T>
Vec3<T> Vec3<T>::Up()
{
	return Vec3<T>(0, 1, 0);
}

template <typename T>
Vec3<T> Vec3<T>::Down()
{
	return Vec3<T>(0, -1, 0);
}

template <typename T>
Vec3<T> Vec3<T>::Left()
{
	return Vec3<T>(-1, 0, 0);
}

template <typename T>
Vec3<T> Vec3<T>::Right()
{
	return Vec3<T>(1, 0, 0);
}

template <typename T>
Vec3<T> Vec3<T>::Back()
{
	return Vec3<T>(0, 0, 1);
}

template <typename T>
Vec3<T> Vec3<T>::Forward()
{
	return Vec3<T>(0, 0, -1);
}

template <typename T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator*=(const T scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator/=(const T scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}
