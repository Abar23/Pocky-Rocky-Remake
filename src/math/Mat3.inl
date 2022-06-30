#pragma once

#include <utility>
#include <cstring>
#include <cmath>
#include <cstdint>
#include "MathFunctions.h"


template <typename T>
Mat3<T>::Mat3()
	: data{ 0 }
{
}

template<typename T>
Mat3<T>::Mat3(std::initializer_list<T> args)
{
	std::uint8_t column = 0, row = 0;
	for (auto& element : args)
	{
		data[column][row] = element;
		column++;
		if (column == 3)
		{
			column = 0;
			row++;
		}
	}
}

template <typename T>
Mat3<T>::Mat3(const T m00, const T m01, const T m02,
				const T m10, const T m11, const T m12, 
				const T m20, const T m21, const T m22)
{
	// Column-major ordering
	data[0][0] = m00;
	data[0][1] = m10;
	data[0][2] = m20;

	data[1][0] = m01;
	data[1][1] = m11;
	data[1][2] = m21;

	data[2][0] = m02;
	data[2][1] = m12;
	data[2][2] = m22;
}

template <typename T>
Mat3<T>::Mat3(const Vec3<T>& firstRow,
				const Vec3<T>& secondRow, 
				const Vec3<T>& thirdRow)
{
	// Column-major ordering
	data[0][0] = firstRow.x;
	data[1][0] = firstRow.y;
	data[2][0] = firstRow.z;

	data[0][1] = secondRow.x;
	data[1][1] = secondRow.y;
	data[2][1] = secondRow.z;

	data[0][2] = thirdRow.x;
	data[1][2] = thirdRow.y;
	data[2][2] = thirdRow.z;
}

template <typename T>
Mat3<T>::Mat3(const T diagonal)
	: data{ 0 }
{
	data[0][0] = diagonal;
	data[1][1] = diagonal;
	data[2][2] = diagonal;
}

template <typename T>
Mat3<T>::Mat3(const Mat3<T>& matrix)
{
	std::memcpy(data, matrix.data, sizeof(Mat3<T>));
}

template <typename T>
Mat3<T> Mat3<T>::Inverted() const
{
	const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(data[0]);
	const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(data[1]);
	const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(data[2]);

	Vec3<T> bCrossC = Vec3<T>::Cross(b, c);
	Vec3<T> cCrossa = Vec3<T>::Cross(c, a);
	Vec3<T> aCrossb = Vec3<T>::Cross(a, b);

	T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(aCrossb, c);

	return Mat3<T>(bCrossC.x * inverseDet, bCrossC.y * inverseDet, bCrossC.z * inverseDet, 
					cCrossa.x * inverseDet, cCrossa.y * inverseDet, cCrossa.z * inverseDet,
					aCrossb.x * inverseDet, aCrossb.y * inverseDet, aCrossb.z * inverseDet);
}

template <typename T>
Mat3<T>& Mat3<T>::Invert()
{
	const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(data[0]);
	const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(data[1]);
	const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(data[2]);

	Vec3<T> bCrossC = Vec3<T>::Cross(b, c);
	Vec3<T> cCrossa = Vec3<T>::Cross(c, a);
	Vec3<T> aCrossb = Vec3<T>::Cross(a, b);

	T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(aCrossb, c);

	data[0][0] = bCrossC.x * inverseDet;
	data[0][1] = cCrossa.x * inverseDet;
	data[0][2] = aCrossb.x * inverseDet;

	data[1][0] = bCrossC.y * inverseDet;
	data[1][1] = cCrossa.y * inverseDet;
	data[1][2] = aCrossb.y * inverseDet;

	data[2][0] = bCrossC.z * inverseDet;
	data[2][1] = cCrossa.z * inverseDet;
	data[2][2] = aCrossb.z * inverseDet;

	return *this;
}

template <typename T>
Mat3<T> Mat3<T>::Transposed() const
{
	return Mat3<T>(data[0][0], data[0][1], data[0][2], 
					data[1][0], data[1][1], data[1][2], 
					data[2][0], data[2][1], data[2][2]);
}

template <typename T>
Mat3<T>& Mat3<T>::Transpose()
{
	Mat3<T> temp = *this;

	data[0][1] = temp.data[1][0];
	data[0][2] = temp.data[2][0];

	data[1][0] = temp.data[0][1];
	data[1][2] = temp.data[2][1];

	data[2][0] = temp.data[0][2];
	data[2][1] = temp.data[1][2];

	return *this;
}

template <typename T>
T Mat3<T>::Determinant() const
{
	return data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2])
			+ data[1][0] * (data[2][1] * data[0][2] - data[0][1] * data[2][2])
			+ data[2][0] * (data[0][1] * data[1][2] - data[1][1] * data[0][2]);
}

template <typename T>
Vec3<T> Mat3<T>::GetColumn(const int columnIndex) const
{
	return columns[columnIndex];
}

template <typename T>
void Mat3<T>::SetColumn(const int columnIndex, const Vec3<T>& vector)
{
	columns[columnIndex] = vector;
}

template <typename T>
Vec3<T> Mat3<T>::GetRow(const int rowIndex) const
{
	return Vec3<T>(data[0][rowIndex],
					data[1][rowIndex],
					data[2][rowIndex]);
}

template <typename T>
void Mat3<T>::SetRow(const int rowIndex, const Vec3<T>& vector)
{
	data[0][rowIndex] = vector.x;
	data[1][rowIndex] = vector.y;
	data[2][rowIndex] = vector.z;
}

template <typename T>
Mat3<T> Mat3<T>::MakeRotationX(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat3<T>(1, 0, 0,
					0, cos, -sin,
					0, sin, cos);
}

template <typename T>
Mat3<T> Mat3<T>::MakeRotationY(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat3<T>(cos, 0, sin,
					0, 1, 0,
					-sin, 0, cos);
}

template <typename T>
Mat3<T> Mat3<T>::MakeRotationZ(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat3<T>(cos, -sin, 0,
					sin, cos, 0,
					0, 0, 1);
}

template <typename T>
Mat3<T> Mat3<T>::MakeRotation(const Vec3<T>& axis, const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);
	T oneMinsCos = static_cast<T>(1) - cos;

	T x = axis.x * oneMinsCos;
	T y = axis.y * oneMinsCos;
	T z = axis.z * oneMinsCos;
	T axisXAxisY = x * axis.y;
	T axisXAxisZ = x * axis.z;
	T axisYAxisZ = y * axis.z;

	return Mat3<T>(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y,
				axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x,
				axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z);
}

template <typename T>
Mat3<T> Mat3<T>::MakeScale(const T uniformScale)
{
	return Mat3<T>(uniformScale, 0, 0,
					0, uniformScale, 0,
					0, 0, uniformScale);
}

template <typename T>
Mat3<T> Mat3<T>::MakeScale(const T scaleX, const T scaleY, const T scaleZ)
{
	return Mat3<T>(scaleX, 0, 0,
					0, scaleY, 0,
					0, 0, scaleZ);
}

template <typename T>
Mat3<T> Mat3<T>::MakeScale(const Vec3<T>& vector)
{
	return Mat3<T>(vector.x, 0, 0,
					0, vector.y, 0,
					0, 0, vector.z);
}

template <typename T>
Mat3<T> Mat3<T>::Identity()
{
	return Mat3<T>(1);
}

template <typename T>
Mat3<T>& Mat3<T>::operator=(const Mat3<T>& matrix)
{
	std::memcpy(data, matrix.data, sizeof(Mat3<T>));
	return *this;
}

template<typename T>
inline const T& Mat3<T>::operator()(const int rowIndex, const int columnIndex) const
{
	return data[columnIndex][rowIndex];
}

template<typename T>
inline T& Mat3<T>::operator()(const int rowIndex, const int columnIndex)
{
	return data[columnIndex][rowIndex];
}

template <typename T>
Mat3<T>& Mat3<T>::operator*=(const Mat3<T>& matrix)
{
	Mat3<T> temp = *this;

	data[0][0] = temp.data[0][0] * matrix.data[0][0] + temp.data[1][0] * matrix.data[0][1] + temp.data[2][0] * matrix.data[0][2];
	data[1][0] = temp.data[0][0] * matrix.data[1][0] + temp.data[1][0] * matrix.data[1][1] + temp.data[2][0] * matrix.data[1][2];
	data[2][0] = temp.data[0][0] * matrix.data[2][0] + temp.data[1][0] * matrix.data[2][1] + temp.data[2][0] * matrix.data[2][2];

	data[0][1] = temp.data[0][1] * matrix.data[0][0] + temp.data[1][1] * matrix.data[0][1] + temp.data[2][1] * matrix.data[0][2];
	data[1][1] = temp.data[0][1] * matrix.data[1][0] + temp.data[1][1] * matrix.data[1][1] + temp.data[2][1] * matrix.data[1][2];
	data[2][1] = temp.data[0][1] * matrix.data[2][0] + temp.data[1][1] * matrix.data[2][1] + temp.data[2][1] * matrix.data[2][2];

	data[0][2] = temp.data[0][2] * matrix.data[0][0] + temp.data[1][2] * matrix.data[0][1] + temp.data[2][2] * matrix.data[0][2];
	data[1][2] = temp.data[0][2] * matrix.data[1][0] + temp.data[1][2] * matrix.data[1][1] + temp.data[2][2] * matrix.data[1][2];
	data[2][2] = temp.data[0][2] * matrix.data[2][0] + temp.data[1][2] * matrix.data[2][1] + temp.data[2][2] * matrix.data[2][2];

	return *this;
}

template <typename T>
Mat3<T>& Mat3<T>::operator*=(const T scalar)
{
	columns[0] *= scalar;
	columns[1] *= scalar;
	columns[2] *= scalar;
			
	return *this;
}

template <typename T>
Mat3<T> operator*(const Mat3<T>& leftMatrix, const Mat3<T>& rightMatrix)
{
	Mat3<T> leftMatrixCopy = leftMatrix;
	return leftMatrixCopy *= rightMatrix;
}

template <typename T>
Mat3<T> operator*(const Mat3<T>& matrix, const T scalar)
{
	Mat3<T> matrixCopy = matrix;
	return matrixCopy *= scalar;
}

template<typename T>
Mat3<T> operator*(const T scalar, const Mat3<T>& matrix)
{
	Mat3<T> matrixCopy = matrix;
	return matrixCopy *= scalar;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Mat3<T>& matrix)
{
	stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << std::endl;
	stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << std::endl;
	stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << " )";
	return stream;
}
