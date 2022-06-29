#pragma once

#include <initializer_list>
#include "Vec3.h"

template <typename T>
class Mat3
{
public:
	union
	{
		T data[3][3];

		Vec3<T> columns[3];
	};

	Mat3();
	Mat3(std::initializer_list<T> args);
	Mat3(const T m00, const T m01, const T m02,
			const T m10, const T m11, const T m12,
			const T m20, const T m21, const T m22);
	Mat3(const Vec3<T>& firstRow, 
			const Vec3<T>& secondRow, 
			const Vec3<T>& thirdRow);
	Mat3(const T diagonal);
	Mat3(const Mat3<T>& matrix);

	~Mat3() = default;

	Mat3<T> Inverted() const;
	Mat3<T>& Invert();
	Mat3<T> Transposed() const;
	Mat3<T>& Transpose();
	T Determinant() const;
	Vec3<T> GetColumn(const int columnIndex) const;
	void SetColumn(const int columnIndex, const Vec3<T>& vector);
	Vec3<T> GetRow(const int rowIndex) const;
	void SetRow(const int rowIndex, const Vec3<T>& vector);

	static Mat3<T> MakeRotationX(const T angleInDegrees);
	static Mat3<T> MakeRotationY(const T angleInDegrees);
	static Mat3<T> MakeRotationZ(const T angleInDegrees);
	static Mat3<T> MakeRotation(const Vec3<T>& axis, const T angleInDegrees);
	static Mat3<T> MakeScale(const T uniformScale);
	static Mat3<T> MakeScale(const T scaleX, const T scaleY, const T scaleZ);
	static Mat3<T> MakeScale(const Vec3<T>& vector);
	static Mat3<T> Identity();

	Mat3<T>& operator=(const Mat3<T>& matrix);
			
	const T& operator()(const int rowIndex, const int columnIndex) const;
	T& operator()(const int rowIndex, const int columnIndex);

	Mat3<T>& operator*=(const Mat3<T>& matrix);
	Mat3<T>& operator*=(const T scalar);

	friend Vec3<T> operator*(const Mat3<T>& matrix, const Vec3<T>& vector)
	{
		return Vec3<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z);
	}
};

template <typename T>
Mat3<T> operator*(const Mat3<T>& leftMatrix, const Mat3<T>& rightMatrix);

template <typename T>
Mat3<T> operator*(const Mat3<T>& matrix, const T scalar);

template <typename T>
Mat3<T> operator*(const T scalar, const Mat3<T>& matrix);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Mat3<T>& matrix);

using mat3 = Mat3<float>;
using dmat3 = Mat3<double>;

#include "Mat3.inl"
