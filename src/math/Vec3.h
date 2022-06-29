#pragma once

#include "Vec2.h"

template <typename T> class Vec4;

template <typename T>
class alignas(16) Vec3
{
public:
	union
	{				
		std::array<T, 3> data;
				
		struct
		{
			T x, y, z;
		};

		Swizzle<Vec2, T, 3, 0, 0> xx;
		Swizzle<Vec2, T, 3, 0, 1> xy;
		Swizzle<Vec2, T, 3, 0, 2> xz;
		Swizzle<Vec2, T, 3, 1, 0> yx;
		Swizzle<Vec2, T, 3, 1, 1> yy;
		Swizzle<Vec2, T, 3, 1, 2> yz;
		Swizzle<Vec2, T, 3, 2, 0> zx;
		Swizzle<Vec2, T, 3, 2, 1> zy;
		Swizzle<Vec2, T, 3, 2, 2> zz;

		Swizzle<Vec3, T, 3, 0, 0, 0> xxx;
		Swizzle<Vec3, T, 3, 0, 0, 1> xxy;
		Swizzle<Vec3, T, 3, 0, 0, 2> xxz;
		Swizzle<Vec3, T, 3, 0, 1, 0> xyx;
		Swizzle<Vec3, T, 3, 0, 1, 1> xyy;
		Swizzle<Vec3, T, 3, 0, 1, 2> xyz;
		Swizzle<Vec3, T, 3, 0, 2, 0> xzx;
		Swizzle<Vec3, T, 3, 0, 2, 1> xzy;
		Swizzle<Vec3, T, 3, 0, 2, 2> xzz;
		Swizzle<Vec3, T, 3, 1, 0, 0> yxx;
		Swizzle<Vec3, T, 3, 1, 0, 1> yxy;
		Swizzle<Vec3, T, 3, 1, 0, 2> yxz;
		Swizzle<Vec3, T, 3, 1, 1, 0> yyx;
		Swizzle<Vec3, T, 3, 1, 1, 1> yyy;
		Swizzle<Vec3, T, 3, 1, 1, 2> yyz;
		Swizzle<Vec3, T, 3, 1, 2, 0> yzx;
		Swizzle<Vec3, T, 3, 1, 2, 1> yzy;
		Swizzle<Vec3, T, 3, 1, 2, 2> yzz;
		Swizzle<Vec3, T, 3, 2, 0, 0> zxx;
		Swizzle<Vec3, T, 3, 2, 0, 1> zxy;
		Swizzle<Vec3, T, 3, 2, 0, 2> zxz;
		Swizzle<Vec3, T, 3, 2, 1, 0> zyx;
		Swizzle<Vec3, T, 3, 2, 1, 1> zyy;
		Swizzle<Vec3, T, 3, 2, 1, 2> zyz;
		Swizzle<Vec3, T, 3, 2, 2, 0> zzx;
		Swizzle<Vec3, T, 3, 2, 2, 1> zzy;
		Swizzle<Vec3, T, 3, 2, 2, 2> zzz;

		Swizzle<Vec4, T, 3, 0, 0, 0, 0> xxxx;
		Swizzle<Vec4, T, 3, 0, 0, 0, 1> xxxy;
		Swizzle<Vec4, T, 3, 0, 0, 0, 2> xxxz;
		Swizzle<Vec4, T, 3, 0, 0, 1, 0> xxyx;
		Swizzle<Vec4, T, 3, 0, 0, 1, 1> xxyy;
		Swizzle<Vec4, T, 3, 0, 0, 1, 2> xxyz;
		Swizzle<Vec4, T, 3, 0, 0, 2, 0> xxzx;
		Swizzle<Vec4, T, 3, 0, 0, 2, 1> xxzy;
		Swizzle<Vec4, T, 3, 0, 0, 2, 2> xxzz;
		Swizzle<Vec4, T, 3, 0, 1, 0, 0> xyxx;
		Swizzle<Vec4, T, 3, 0, 1, 0, 1> xyxy;
		Swizzle<Vec4, T, 3, 0, 1, 0, 2> xyxz;
		Swizzle<Vec4, T, 3, 0, 1, 1, 0> xyyx;
		Swizzle<Vec4, T, 3, 0, 1, 1, 1> xyyy;
		Swizzle<Vec4, T, 3, 0, 1, 1, 2> xyyz;
		Swizzle<Vec4, T, 3, 0, 1, 2, 0> xyzx;
		Swizzle<Vec4, T, 3, 0, 1, 2, 1> xyzy;
		Swizzle<Vec4, T, 3, 0, 1, 2, 2> xyzz;
		Swizzle<Vec4, T, 3, 0, 2, 0, 0> xzxx;
		Swizzle<Vec4, T, 3, 0, 2, 0, 1> xzxy;
		Swizzle<Vec4, T, 3, 0, 2, 0, 2> xzxz;
		Swizzle<Vec4, T, 3, 0, 2, 1, 0> xzyx;
		Swizzle<Vec4, T, 3, 0, 2, 1, 1> xzyy;
		Swizzle<Vec4, T, 3, 0, 2, 1, 2> xzyz;
		Swizzle<Vec4, T, 3, 0, 2, 2, 0> xzzx;
		Swizzle<Vec4, T, 3, 0, 2, 2, 1> xzzy;
		Swizzle<Vec4, T, 3, 0, 2, 2, 2> xzzz;
		Swizzle<Vec4, T, 3, 1, 0, 0, 0> yxxx;
		Swizzle<Vec4, T, 3, 1, 0, 0, 1> yxxy;
		Swizzle<Vec4, T, 3, 1, 0, 0, 2> yxxz;
		Swizzle<Vec4, T, 3, 1, 0, 1, 0> yxyx;
		Swizzle<Vec4, T, 3, 1, 0, 1, 1> yxyy;
		Swizzle<Vec4, T, 3, 1, 0, 1, 2> yxyz;
		Swizzle<Vec4, T, 3, 1, 0, 2, 0> yxzx;
		Swizzle<Vec4, T, 3, 1, 0, 2, 1> yxzy;
		Swizzle<Vec4, T, 3, 1, 0, 2, 2> yxzz;
		Swizzle<Vec4, T, 3, 1, 1, 0, 0> yyxx;
		Swizzle<Vec4, T, 3, 1, 1, 0, 1> yyxy;
		Swizzle<Vec4, T, 3, 1, 1, 0, 2> yyxz;
		Swizzle<Vec4, T, 3, 1, 1, 1, 0> yyyx;
		Swizzle<Vec4, T, 3, 1, 1, 1, 1> yyyy;
		Swizzle<Vec4, T, 3, 1, 1, 1, 2> yyyz;
		Swizzle<Vec4, T, 3, 1, 1, 2, 0> yyzx;
		Swizzle<Vec4, T, 3, 1, 1, 2, 1> yyzy;
		Swizzle<Vec4, T, 3, 1, 1, 2, 2> yyzz;
		Swizzle<Vec4, T, 3, 1, 2, 0, 0> yzxx;
		Swizzle<Vec4, T, 3, 1, 2, 0, 1> yzxy;
		Swizzle<Vec4, T, 3, 1, 2, 0, 2> yzxz;
		Swizzle<Vec4, T, 3, 1, 2, 1, 0> yzyx;
		Swizzle<Vec4, T, 3, 1, 2, 1, 1> yzyy;
		Swizzle<Vec4, T, 3, 1, 2, 1, 2> yzyz;
		Swizzle<Vec4, T, 3, 1, 2, 2, 0> yzzx;
		Swizzle<Vec4, T, 3, 1, 2, 2, 1> yzzy;
		Swizzle<Vec4, T, 3, 1, 2, 2, 2> yzzz;
		Swizzle<Vec4, T, 3, 2, 0, 0, 0> zxxx;
		Swizzle<Vec4, T, 3, 2, 0, 0, 1> zxxy;
		Swizzle<Vec4, T, 3, 2, 0, 0, 2> zxxz;
		Swizzle<Vec4, T, 3, 2, 0, 1, 0> zxyx;
		Swizzle<Vec4, T, 3, 2, 0, 1, 1> zxyy;
		Swizzle<Vec4, T, 3, 2, 0, 1, 2> zxyz;
		Swizzle<Vec4, T, 3, 2, 0, 2, 0> zxzx;
		Swizzle<Vec4, T, 3, 2, 0, 2, 1> zxzy;
		Swizzle<Vec4, T, 3, 2, 0, 2, 2> zxzz;
		Swizzle<Vec4, T, 3, 2, 1, 0, 0> zyxx;
		Swizzle<Vec4, T, 3, 2, 1, 0, 1> zyxy;
		Swizzle<Vec4, T, 3, 2, 1, 0, 2> zyxz;
		Swizzle<Vec4, T, 3, 2, 1, 1, 0> zyyx;
		Swizzle<Vec4, T, 3, 2, 1, 1, 1> zyyy;
		Swizzle<Vec4, T, 3, 2, 1, 1, 2> zyyz;
		Swizzle<Vec4, T, 3, 2, 1, 2, 0> zyzx;
		Swizzle<Vec4, T, 3, 2, 1, 2, 1> zyzy;
		Swizzle<Vec4, T, 3, 2, 1, 2, 2> zyzz;
		Swizzle<Vec4, T, 3, 2, 2, 0, 0> zzxx;
		Swizzle<Vec4, T, 3, 2, 2, 0, 1> zzxy;
		Swizzle<Vec4, T, 3, 2, 2, 0, 2> zzxz;
		Swizzle<Vec4, T, 3, 2, 2, 1, 0> zzyx;
		Swizzle<Vec4, T, 3, 2, 2, 1, 1> zzyy;
		Swizzle<Vec4, T, 3, 2, 2, 1, 2> zzyz;
		Swizzle<Vec4, T, 3, 2, 2, 2, 0> zzzx;
		Swizzle<Vec4, T, 3, 2, 2, 2, 1> zzzy;
		Swizzle<Vec4, T, 3, 2, 2, 2, 2> zzzz;
	};

	Vec3();
	Vec3(const Vec3<T>& v) = default;
	Vec3(std::initializer_list<T> args);
	Vec3(const T x, const T y, const T z);
	Vec3(const T value);

	~Vec3() = default;

	T Magnitude() const;
	T SqrMagnitude() const;
	Vec3<T> Normalize() const;
	Vec3<T>& Normalized();
	Vec3<T> Renormalized() const;
	Vec3<T>& Renormalize();
	Vec3<T> Negated() const;
	Vec3<T>& Negate();

	static T Dot(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
	static Vec3<T> Cross(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
	static Vec3<T> Project(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
	static Vec3<T> Reject(const Vec3<T>& leftVector, const Vec3<T>& rightVector);
	static Vec3<T> Lerp(const Vec3<T>& leftVector, const Vec3<T>& rightVector, const float t);
	static Vec3<T> Zero();
	static Vec3<T> XAxis();
	static Vec3<T> YAxis();
	static Vec3<T> ZAxis();
	static Vec3<T> Up();
	static Vec3<T> Down();
	static Vec3<T> Left();
	static Vec3<T> Right();
	static Vec3<T> Back();
	static Vec3<T> Forward();

	Vec3<T>& operator=(const Vec3<T>& vector);
	Vec3<T>& operator+=(const Vec3<T>& vector);
	Vec3<T>& operator-=(const Vec3<T>& vector);

	Vec3<T>& operator*=(const T scalar);
	Vec3<T>& operator/=(const T scalar);

	friend bool operator==(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
	{
		return NearEquals(leftVector.x, rightVector.x) &&
			NearEquals(leftVector.y, rightVector.y) &&
			NearEquals(leftVector.z, rightVector.z);
	}

	friend bool operator!=(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
	{
		return !(leftVector == rightVector);
	}

	friend Vec3<T> operator+(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
	{
		Vec3<T> leftVectorCopy = leftVector;
		return leftVectorCopy += rightVector;
	}

	friend Vec3<T> operator-(const Vec3<T>& leftVector, const Vec3<T>& rightVector)
	{
		Vec3<T> leftVectorCopy = leftVector;
		return leftVectorCopy -= rightVector;
	}

	friend Vec3<T> operator*(const Vec3<T>& vector, const T scalar)
	{
		Vec3<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec3<T> operator*(const T scalar, const Vec3<T>& vector)
	{
		Vec3<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec3<T> operator/(const Vec3<T>& vector, const T scalar)
	{
		Vec3<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend Vec3<T> operator/(const T scalar, const Vec3<T>& vector)
	{
		Vec3<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vec3<T>& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}
};

using ivec3 = Vec3<int>;
using uvec3 = Vec3<unsigned int>;
using vec3 = Vec3<float>;
using dvec3 = Vec3<double>;

#include "Vec3.inl"
