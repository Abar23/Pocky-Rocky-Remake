#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"

template <typename T>
class Quaternion
{
public:
	union
	{
		struct {
			T x, y, z, w;
		};

		Vec4<T> components;
	};

	Quaternion();
	Quaternion(const T x, const T y, const T z, const T w);
	Quaternion(const Vec3<T>& unitVector, const T angleInDegrees);
	Quaternion(const Quaternion<T>& quaternion);

	~Quaternion() = default;

	T Norm() const;
	T SqrNorm() const;
	Quaternion<T> Normalized() const;
	Quaternion<T>& Normalize();
	Quaternion<T> Renormalized() const;
	Quaternion<T>& Renormalize();
	Quaternion<T> Inverted() const;
	Quaternion<T>& Invert();
	Quaternion<T> Conjugate() const;
	Mat3<T> GetRotationMatrix() const;
	void SetRotationMatrix(const Mat3<T>& matrix);

	static Vec3<T> TransformVector(const Quaternion<T>& quaterion, const Vec3<T>& vector);
	static T Dot(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion);
	static Quaternion<T> MakeRotationX(const T angleInDegrees);
	static Quaternion<T> MakeRotationY(const T angleInDegrees);
	static Quaternion<T> MakeRotationZ(const T angleInDegrees);
	static Quaternion<T> MakeRotation(const Vec3<T>& unitVector, const T angleInDegrees);
	static Quaternion<T> Lerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t);
	static Quaternion<T> Nlerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t);
	static Quaternion<T> Slerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t);

	Quaternion<T>& operator=(const Quaternion<T>& quaternion);
	Quaternion<T>& operator*=(const Quaternion<T>& quaterion);
	Quaternion<T>& operator*=(const T scalar);
	Quaternion<T>& operator/=(const T scalar);
	Quaternion<T>& operator+=(const Quaternion<T>& quaternion);
	Quaternion<T>& operator-=(const Quaternion<T>& quaternion);

	friend Vec3<T> operator*(const Quaternion<T>& quaternion, const Vec3<T>& vector)
	{
		return Quaternion<T>::TransformVector(quaternion, vector);
	}
};

template <typename T>
Quaternion<T> operator*(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion);

template <typename T>
Quaternion<T> operator*(const Quaternion<T>& quaterion, const T scalar);

template <typename T>
Quaternion<T> operator*(const T scalar, const Quaternion<T>& quaterion);

template <typename T>
Quaternion<T> operator/(const Quaternion<T>& quaterion, const T scalar);

template <typename T>
Quaternion<T> operator/(const T scalar, const Quaternion<T>& quaterion);

template <typename T>
Quaternion<T> operator+(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion);

template <typename T>
Quaternion<T> operator-(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& quaternion);

using quat = Quaternion<float>;
using quatd = Quaternion<double>;

#include "Quaternion.inl"