#pragma once

#include <ostream>
#include <initializer_list>
#include <array>
#include "Swizzle.h"
#include "MathFunctions.h"

template <typename T> class Vec3;
template <typename T> class Vec4;

template <typename T>
class Vec2
{
public:
	union
	{
		std::array<T, 2> data;

		struct
		{
			T x, y;
		};

		Swizzle<Vec2, T, 2, 0, 0> xx;
		Swizzle<Vec2, T, 2, 0, 1> xy;
		Swizzle<Vec2, T, 2, 1, 0> yx;
		Swizzle<Vec2, T, 2, 1, 1> yy;

		Swizzle<Vec3, T, 2, 0, 0, 0> xxx;
		Swizzle<Vec3, T, 2, 0, 0, 1> xxy;
		Swizzle<Vec3, T, 2, 0, 1, 0> xyx;
		Swizzle<Vec3, T, 2, 0, 1, 1> xyy;
		Swizzle<Vec3, T, 2, 1, 0, 0> yxx;
		Swizzle<Vec3, T, 2, 1, 0, 1> yxy;
		Swizzle<Vec3, T, 2, 1, 1, 0> yyx;
		Swizzle<Vec3, T, 2, 1, 1, 1> yyy;

		Swizzle<Vec4, T, 2, 0, 0, 0, 0> xxxx;
		Swizzle<Vec4, T, 2, 0, 0, 0, 1> xxxy;
		Swizzle<Vec4, T, 2, 0, 0, 1, 0> xxyx;
		Swizzle<Vec4, T, 2, 0, 0, 1, 1> xxyy;
		Swizzle<Vec4, T, 2, 0, 1, 0, 0> xyxx;
		Swizzle<Vec4, T, 2, 0, 1, 0, 1> xyxy;
		Swizzle<Vec4, T, 2, 0, 1, 1, 0> xyyx;
		Swizzle<Vec4, T, 2, 0, 1, 1, 1> xyyy;
		Swizzle<Vec4, T, 2, 1, 0, 0, 0> yxxx;
		Swizzle<Vec4, T, 2, 1, 0, 0, 1> yxxy;
		Swizzle<Vec4, T, 2, 1, 0, 1, 0> yxyx;
		Swizzle<Vec4, T, 2, 1, 0, 1, 1> yxyy;
		Swizzle<Vec4, T, 2, 1, 1, 0, 0> yyxx;
		Swizzle<Vec4, T, 2, 1, 1, 0, 1> yyxy;
		Swizzle<Vec4, T, 2, 1, 1, 1, 0> yyyx;
		Swizzle<Vec4, T, 2, 1, 1, 1, 1> yyyy;
	};

	Vec2();
	Vec2(std::initializer_list<T> args);
	Vec2(const T x, const T y);
	Vec2(const T scalar);
	Vec2(const Vec2<T>& vector);

	~Vec2() = default;

	T Magnitude() const;
	T SqrMagnitude() const;
	Vec2<T> Normalized() const;
	Vec2<T>& Normalize();
	Vec2<T> Renormalized() const;
	Vec2<T>& Renormalize();
	Vec2<T> Negated() const;
	Vec2<T>& Negate();

	static T Dot(const Vec2<T>& leftVector, const Vec2<T>& rightVector);
	static Vec2<T> Project(const Vec2<T>& leftVector, const Vec2<T>& rightVector);
	static Vec2<T> Reject(const Vec2<T>& leftVector, const Vec2<T>& rightVector);
	static Vec2<T> Lerp(const Vec2<T>& leftVector, const Vec2<T>& rightVector, const T t);
	static Vec2<T> Zero();
	static Vec2<T> XAxis();
	static Vec2<T> YAxis();
	static Vec2<T> Up();
	static Vec2<T> Down();
	static Vec2<T> Left();
	static Vec2<T> Right();

	Vec2<T>& operator=(const Vec2<T>& vector);
	__forceinline Vec2<T>& operator+=(const Vec2<T>& vector);
	Vec2<T>& operator-=(const Vec2<T>& vector);

	Vec2<T>& operator*=(const T scalar);
	Vec2<T>& operator/=(const T scalar);

	friend bool operator==(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
	{
		return NearEquals(leftVector.x, rightVector.x) &&
			NearEquals(leftVector.y, rightVector.y);
	}

	friend bool operator!=(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
	{
		return !(leftVector == rightVector);
	}

	friend Vec2<T> operator+(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
	{
		Vec2<T> leftVectorCopy = leftVector;
		return leftVectorCopy += rightVector;
	}

	friend Vec2<T> operator-(const Vec2<T>& leftVector, const Vec2<T>& rightVector)
	{
		Vec2<T> leftVectorCopy = leftVector;
		return leftVectorCopy -= rightVector;
	}

	friend Vec2<T> operator*(const Vec2<T>& vector, const T scalar)
	{
		Vec2<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec2<T> operator*(const T scalar, const Vec2<T>& vector)
	{
		Vec2<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec2<T> operator/(const Vec2<T>& vector, const T scalar)
	{
		Vec2<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend Vec2<T> operator/(const T scalar, const Vec2<T>& vector)
	{
		Vec2<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ")";
		return stream;
	}
};

using ivec2 = Vec2<int>;
using uvec2 = Vec2<unsigned int>;
using vec2 = Vec2<float>;
using dvec2 = Vec2<double>;

#include "Vec2.inl"
