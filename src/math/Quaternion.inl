#pragma once

#include <cmath>
#include <algorithm>
#include "MathFunctions.h"
#include "MathConstants.h"

template <typename T>
Quaternion<T>::Quaternion()
	: x(0), y(0), z(0), w(1)
{
}

template <typename T>
Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w)
	: x(x), y(y), z(z), w(w)
{
}

template <typename T>
Quaternion<T>::Quaternion(const Vec3<T>& unitVector, const T angleInDegrees)
{
	T halfAngle = DegreesToRad(angleInDegrees) / static_cast<T>(2);
	T cosHalfAngle = std::cos(halfAngle);
	T sinHalfAngle = std::sin(halfAngle);

	x = unitVector.x * sinHalfAngle;
	y = unitVector.y * sinHalfAngle;
	z = unitVector.z * sinHalfAngle;
	w = cosHalfAngle;
}

template <typename T>
Quaternion<T>::Quaternion(const Quaternion<T>& quaternion)
	: x(quaternion.x), y(quaternion.y), z(quaternion.z), w(quaternion.w)
{
}

template <typename T>
T Quaternion<T>::Norm() const
{
	return std::sqrt(SqrNorm());
}

template <typename T>
T Quaternion<T>::SqrNorm() const
{
	return x * x + y * y + z * z + w * w;
}

template <typename T>
Quaternion<T> Quaternion<T>::Normalized() const
{
	T norm = Norm();
	return Quaternion<T>(x / norm, y / norm, z / norm, w / norm);
}

template<typename T>
Quaternion<T>& Quaternion<T>::Normalize()
{
	T norm = Norm();
	this->x /= norm;
	this->y /= norm;
	this->z /= norm;
	this->w /= norm;
	return *this;
}

template <typename T>
Quaternion<T> Quaternion<T>::Renormalized() const
{
	T inverseNorm = FastInverseSqurRootAroundOne(SqrNorm());
	return Quaternion<T>(x * inverseNorm, y * inverseNorm, z * inverseNorm, w * inverseNorm);
}

template <typename T>
Quaternion<T>& Quaternion<T>::Renormalize()
{
	T inverseNorm = FastInverseSqurRootAroundOne(SqrNorm());
	*this *= inverseNorm;
	return *this;
}

template <typename T>
Quaternion<T> Quaternion<T>::Inverted() const
{
	return Conjugate();
}

template <typename T>
Quaternion<T>& Quaternion<T>::Invert()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

template <typename T>
Quaternion<T> Quaternion<T>::Conjugate() const
{
	return Quaternion<T>(-x, -y, -z, w);
}

template <typename T>
Mat3<T> Quaternion<T>::GetRotationMatrix() const
{
	Mat3<T> matrix;

	T xSquared = x * x;
	T ySquared = y * y;
	T zSquared = z * z;
	T xy = x * y;
	T xz = x * z;
	T yz = y * z;
	T wx = w * x;
	T wy = w * y;
	T wz = w * z;

	matrix(0, 0) = static_cast<T>(1) - static_cast<T>(2) * (ySquared + zSquared);
	matrix(1, 0) = static_cast<T>(2) * (xy + wz);
	matrix(2, 0) = static_cast<T>(2) * (xz - wy);

	matrix(0, 1) = static_cast<T>(2) * (xy - wz);
	matrix(1, 1) = static_cast<T>(1) - static_cast<T>(2) * (xSquared + zSquared);
	matrix(2, 1) = static_cast<T>(2) * (yz + wx);

	matrix(0, 2) = static_cast<T>(2) * (xz + wy);
	matrix(1, 2) = static_cast<T>(2) * (yz - wx);
	matrix(2, 2) = static_cast<T>(1) - static_cast<T>(2) * (xSquared + ySquared);

	return matrix;
}

template <typename T>
void Quaternion<T>::SetRotationMatrix(const Mat3<T>& matrix)
{
	T m00 = matrix(0, 0);
	T m11 = matrix(1, 1);
	T m22 = matrix(2, 2);
	T diagonalSum = m00 + m11 + m22;

	if (diagonalSum > 0)
	{
		w = std::sqrt(diagonalSum + static_cast<T>(1)) * static_cast<T>(0.5);
		T fraction = static_cast<T>(0.25) / w;

		x = (matrix(2, 1) - matrix(1, 2)) * fraction;
		y = (matrix(0, 2) - matrix(2, 0)) * fraction;
		z = (matrix(1, 0) - matrix(0, 1)) * fraction;
	}
	else if (m00 > m11 && m00 > m22)
	{
		x = std::sqrt(m00 - m11 - m22 + static_cast<T>(1)) * static_cast<T>(0.5);
		T fraction = static_cast<T>(0.25) / x;

		y = (matrix(1, 0) + matrix(0, 1)) * fraction;
		z = (matrix(0, 2) + matrix(2, 0)) * fraction;
		w = (matrix(2, 1) - matrix(1, 2)) * fraction;
	}
	else if (m11 > m22)
	{
		y = std::sqrt(m11 - m00 - m22 + static_cast<T>(1)) * static_cast<T>(0.5);
		T fraction = static_cast<T>(0.25) / y;

		x = (matrix(1, 0) + matrix(0, 1)) * fraction;
		z = (matrix(2, 1) + matrix(1, 2)) * fraction;
		w = (matrix(0, 2) - matrix(2, 0)) * fraction;
	}
	else
	{
		z = std::sqrt(m22 - m00 - m11 + static_cast<T>(1)) * static_cast<T>(0.5);
		T fraction = static_cast<T>(0.25) / z;

		x = (matrix(0, 2) + matrix(2, 0)) * fraction;
		y = (matrix(2, 1) + matrix(1, 2)) * fraction;
		w = (matrix(1, 0) - matrix(0, 1)) * fraction;
	}
}

template <typename T>
Vec3<T> Quaternion<T>::TransformVector(const Quaternion<T>& quaterion, const Vec3<T>& vector)
{
	Vec3<T> vectorPart(quaterion.x, quaterion.y, quaterion.z);
			
	return (vector * (quaterion.w * quaterion.w - vectorPart.SqrMagnitude())) +
			vectorPart * (Vec3<T>::Dot(vector, vectorPart) * static_cast<T>(2)) +
			Vec3<T>::Cross(vectorPart, vector) * (quaterion.w * static_cast<T>(2));
}

template <typename T>
T Quaternion<T>::Dot(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion)
{
	return leftQuaterion.x * rightQuaterion.x + 
			leftQuaterion.y * rightQuaterion.y + 
			leftQuaterion.z * rightQuaterion.z + 
			leftQuaterion.w * rightQuaterion.w;
}

template <typename T>
Quaternion<T> Quaternion<T>::MakeRotationX(const T angleInDegrees)
{
	T halfAngle = DegreesToRad(angleInDegrees) / static_cast<T>(2);
	return Quaternion<T>(std::sin(halfAngle), 0, 0, std::cos(halfAngle));
}

template <typename T>
Quaternion<T> Quaternion<T>::MakeRotationY(const T angleInDegrees)
{
	T halfAngle = DegreesToRad(angleInDegrees) / static_cast<T>(2);
	return Quaternion<T>(0, std::sin(halfAngle), 0, std::cos(halfAngle));
}

template <typename T>
Quaternion<T> Quaternion<T>::MakeRotationZ(const T angleInDegrees)
{
	float halfAngle = DegreesToRad(angleInDegrees) / static_cast<T>(2);
	return Quaternion<T>(0, 0, std::sin(halfAngle), std::cos(halfAngle));
}

template <typename T>
Quaternion<T> Quaternion<T>::MakeRotation(const Vec3<T>& unitVector, const T angleInDegrees)
{
	return Quaternion<T>(unitVector, angleInDegrees);
}

template <typename T>
Quaternion<T> Quaternion<T>::Lerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t)
{
	return leftQuaternion * (static_cast<T>(1) - t) + rightQuaternion * t;
}

template <typename T>
Quaternion<T> Quaternion<T>::Nlerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t)
{
	return Lerp(leftQuaternion, rightQuaternion, t).Normalized();
}

template <typename T>
Quaternion<T> Quaternion<T>::Slerp(const Quaternion<T>& leftQuaternion, const Quaternion<T>& rightQuaternion, const T t)
{
	float dot = Quaternion<T>::Dot(leftQuaternion, rightQuaternion);

	if (dot > dotThreshhold)
	{
		return Nlerp(leftQuaternion, rightQuaternion, t);
	}
			
	dot = std::clamp(dot, static_cast<T>(-1), static_cast<T>(1));
	T theta = std::acos(dot) * t; // Angle between leftQuaternion and new quaternion at t
	Quaternion<T> nlerpedQuaternion = Nlerp(leftQuaternion, rightQuaternion, dot);
	return leftQuaternion * std::cos(theta) + nlerpedQuaternion * std::sin(theta);
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& quaternion)
{
	x = quaternion.x;
	y = quaternion.y;
	z = quaternion.z;
	w = quaternion.w;
	return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& quaterion)
{
	Quaternion<T> temp = *this;
			
	this->x = temp.w * quaterion.x + temp.x * quaterion.w + temp.y * quaterion.z - temp.z * quaterion.y;
	this->y = temp.w * quaterion.y + temp.y * quaterion.w + temp.z * quaterion.x - temp.x * quaterion.z;
	this->z = temp.w * quaterion.z + temp.z * quaterion.w + temp.x * quaterion.y - temp.y * quaterion.x;
	this->w = temp.w * quaterion.w - temp.x * quaterion.x - temp.y * quaterion.y - temp.z * quaterion.z;

	return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator*=(const T scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator/=(const T scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& quaternion)
{
	x += quaternion.x;
	y += quaternion.y;
	z += quaternion.z;
	w += quaternion.w;
	return *this;
}

template <typename T>
Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& quaternion)
{
	x -= quaternion.x;
	y -= quaternion.y;
	z -= quaternion.z;
	w -= quaternion.w;
	return *this;
}

template <typename T>
Quaternion<T> operator*(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion)
{
	Quaternion<T> leftQuaterionCopy = leftQuaterion;
	return leftQuaterionCopy *= rightQuaterion;
}
		
template <typename T>
Quaternion<T> operator*(const Quaternion<T>& quaterion, const T scalar)
{
	Quaternion quaterionCopy = quaterion;
	return quaterionCopy *= scalar;
}

template<typename T>
Quaternion<T> operator*(const T scalar, const Quaternion<T>& quaterion)
{
	Quaternion quaterionCopy = quaterion;
	return quaterionCopy *= scalar;
}

template <typename T>
Quaternion<T> operator/(const Quaternion<T>& quaterion, const T scalar)
{
	Quaternion<T> quaterionCopy = quaterion;
	return quaterionCopy /= scalar;
}

template<typename T>
Quaternion<T> operator/(const T scalar, const Quaternion<T>& quaterion)
{
	Quaternion<T> quaterionCopy = quaterion;
	return quaterionCopy /= scalar;
}

template <typename T>
Quaternion<T> operator+(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion)
{
	Quaternion<T> leftQuaterionCopy = leftQuaterion;
	return leftQuaterionCopy += rightQuaterion;
}

template <typename T>
Quaternion<T> operator-(const Quaternion<T>& leftQuaterion, const Quaternion<T>& rightQuaterion)
{
	Quaternion<T> leftQuaterionCopy = leftQuaterion;
	return leftQuaterionCopy -= rightQuaterion;
}
		
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& quaternion)
{
	stream << "([" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << "], " << quaternion.w << ")";
	return stream;
}