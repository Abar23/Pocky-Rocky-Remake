#pragma once

#include <assert.h>
#include <cmath>
#include "MathConstants.h"
#include "Vec2.h"

template <typename T>
Vec2<T>::Vec2()
	: x(0), y(0)
{
}

template<typename T>
Vec2<T>::Vec2(std::initializer_list<T> args)
{
	int index = 0;
	for (auto begin = args.begin(); begin != args.end(); ++begin)
	{
		this->data.at(index++) = *begin;
	}
}

template <typename T>
Vec2<T>::Vec2(const T x, const T y)
	: x(x), y(y)
{
}

template <typename T>
Vec2<T>::Vec2(const T scalar)
	: x(scalar), y(scalar)
{
}

template <typename T>
Vec2<T>::Vec2(const Vec2& vector)
	: x(vector.x), y(vector.y)
{
}

template <typename T>
Vec2<T> Vec2<T>::Zero()
{
	return Vec2<T>();
}

template <typename T>
Vec2<T> Vec2<T>::XAxis()
{
	return Vec2<T>(1, 0);
}

template <typename T>
Vec2<T> Vec2<T>::YAxis()
{
	return Vec2<T>(0, 1);
}

template <typename T>
Vec2<T> Vec2<T>::Up()
{
	return Vec2<T>(0, 1);
}

template <typename T>
Vec2<T> Vec2<T>::Down()
{
	return Vec2<T>(0, -1);
}

template <typename T>
Vec2<T> Vec2<T>::Left()
{
	return Vec2<T>(-1, 0);
}

template <typename T>
Vec2<T> Vec2<T>::Right()
{
	return Vec2<T>(1, 0);
}

template <typename T>
T Vec2<T>::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

template <typename T>
T Vec2<T>::SqrMagnitude() const
{
	return x * x + y * y;
}

template <typename T>
Vec2<T> Vec2<T>::Normalized() const
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));

	T magnitude = Magnitude();

	return Vec2<T>(x / magnitude, y / magnitude);
}

template <typename T>
Vec2<T>& Vec2<T>::Normalize()
{
	assert(!NearEquals(Magnitude(), static_cast<T>(0)));
			
	*this /= Magnitude();

	return *this;
}

template <typename T>
Vec2<T> Vec2<T>::Renormalized() const
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return Vec2<T>(x * inverseMagnitude, y * inverseMagnitude);
}

template <typename T>
Vec2<T>& Vec2<T>::Renormalize()
{
	T inverseMagnitude = FastInverseSqurRootAroundOne(SqrMagnitude());
	return *this *= inverseMagnitude;
}

template <typename T>
Vec2<T> Vec2<T>::Negated() const
{
	return *this * static_cast<T>(-1);
}

template <typename T>
Vec2<T>& Vec2<T>::Negate()
{
	*this *= static_cast<T>(-1);
	return *this;
}

template <typename T>
T Vec2<T>::Dot(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
{
	return leftVector.x * rightVector.x + leftVector.y * rightVector.y;
}

template <typename T>
Vec2<T> Vec2<T>::Project(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
{
	return rightVector * (Dot(leftVector, rightVector) / Dot(rightVector, rightVector));
}

template <typename T>
Vec2<T> Vec2<T>::Reject(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
{
	return leftVector - Project(leftVector, rightVector);
}

template <typename T>
Vec2<T> Vec2<T>::Lerp(const Vec2<T>& leftVector, const Vec2<T>& rightVector, const T t)
{
	return (leftVector * (static_cast<T>(1) - t)) + (rightVector * t);
}
		
template <typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2<T>& vector)
{	
	x = vector.x;
	y = vector.y;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator*=(const T scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator/=(const T scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}
