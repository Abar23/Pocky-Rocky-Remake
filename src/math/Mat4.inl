#pragma once

#include <cstring>
#include <cmath>
#include <cstdint>
#include "MathFunctions.h"

template <typename T>
Mat4<T>::Mat4()
	: data{ 0 } 
{ }

template<typename T>
Mat4<T>::Mat4(std::initializer_list<T> args)
{
	std::uint8_t column = 0, row = 0;
	for (auto &element : args)
	{
		this->data[column][row] = element;
		column++;
		if (column == 4)
		{
			column = 0;
			row++;
		}
	}
}

template <typename T>
Mat4<T>::Mat4(const T m00, const T m01, const T m02, const T m03,
				const T m10, const T m11, const T m12, const T m13, 
				const T m20, const T m21, const T m22, const T m23, 
				const T m30, const T m31, const T m32, const T m33)
{
	// Column-major ordering
	data[0][0] = m00;
	data[0][1] = m10;
	data[0][2] = m20;
	data[0][3] = m30;

	data[1][0] = m01;
	data[1][1] = m11;
	data[1][2] = m21;
	data[1][3] = m31;

	data[2][0] = m02;
	data[2][1] = m12;
	data[2][2] = m22;
	data[2][3] = m32;

	data[3][0] = m03;
	data[3][1] = m13;
	data[3][2] = m23;
	data[3][3] = m33;
}

template <typename T>
Mat4<T>::Mat4(const Vec4<T>& firstRow,
				const Vec4<T>& secondRow, 
				const Vec4<T>& thirdRow, 
				const Vec4<T>& fourthRow)
{
			
	data[0][0] = firstRow.x;
	data[1][0] = firstRow.y;
	data[2][0] = firstRow.z;
	data[3][0] = firstRow.w;

	data[0][1] = secondRow.x;
	data[1][1] = secondRow.y;
	data[2][1] = secondRow.z;
	data[3][1] = secondRow.w;

	data[0][2] = thirdRow.x;
	data[1][2] = thirdRow.y;
	data[2][2] = thirdRow.z;
	data[3][2] = thirdRow.w;

	data[0][3] = fourthRow.x;
	data[1][3] = fourthRow.y;
	data[2][3] = fourthRow.z;
	data[3][3] = fourthRow.w;
}

template <typename T>
Mat4<T>::Mat4(const T diagonal)
	: data{ 0 }
{
	data[0][0] = diagonal;
	data[1][1] = diagonal;
	data[2][2] = diagonal;
	data[3][3] = diagonal;
}

template <typename T>
Mat4<T>::Mat4(const Mat4<T>& matrix)
{
	std::memcpy(data, matrix.data, sizeof(Mat4<T>));
}

template <typename T>
Mat4<T> Mat4<T>::Inverted() const
{
	const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(data[0]);
	const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(data[1]);
	const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(data[2]);
	const Vec3<T> d = reinterpret_cast<const Vec3<T>&>(data[3]);

	T x = data[0][3];
	T y = data[1][3];
	T z = data[2][3];
	T w = data[3][3];

	Vec3<T> s = Vec3<T>::Cross(a, b);
	Vec3<T> t = Vec3<T>::Cross(c, d);
	Vec3<T> u = a * y - b * x;
	Vec3<T> v = c * w - d * z;

	T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(s, v) - Vec3<T>::Dot(t, u);
	s *= inverseDet;
	t *= inverseDet;
	u *= inverseDet;
	v *= inverseDet;

	Vec3<T> firstRow = Vec3<T>::Cross(b, v) + t * y;
	Vec3<T> secondRow = Vec3<T>::Cross(v, a) - t * x;
	Vec3<T> thirdRow = Vec3<T>::Cross(d, u) + s * w;
	Vec3<T> fourthRow = Vec3<T>::Cross(u, c) - s * z;

	return Mat4<T>(firstRow.x, firstRow.y, firstRow.z, -Vec3<T>::Dot(b, t),
					secondRow.x, secondRow.y, secondRow.z, Vec3<T>::Dot(a, t),
					thirdRow.x, thirdRow.y, thirdRow.z, -Vec3<T>::Dot(d, s),
					fourthRow.x, fourthRow.y, fourthRow.z, Vec3<T>::Dot(c, s));
}

template <typename T>
Mat4<T>& Mat4<T>::Invert()
{
	const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(data[0]);
	const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(data[1]);
	const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(data[2]);
	const Vec3<T> d = reinterpret_cast<const Vec3<T>&>(data[3]);

	T x = data[0][3];
	T y = data[1][3];
	T z = data[2][3];
	T w = data[3][3];

	Vec3<T> s = Vec3<T>::Cross(a, b);
	Vec3<T> t = Vec3<T>::Cross(c, d);
	Vec3<T> u = a * y - b * x;
	Vec3<T> v = c * w - d * z;

	T inverseDet = static_cast<T>(1) / Vec3<T>::Dot(s, v) - Vec3<T>::Dot(t, u);
	s *= inverseDet;
	t *= inverseDet;
	u *= inverseDet;
	v *= inverseDet;

	Vec3<T> firstRow = Vec3<T>::Cross(b, v) + t * y;
	Vec3<T> secondRow = Vec3<T>::Cross(v, a) - t * x;
	Vec3<T> thirdRow = Vec3<T>::Cross(d, u) + s * w;
	Vec3<T> fourthRow = Vec3<T>::Cross(u, c) - s * z;

	data[0][0] = firstRow.x;
	data[1][0] = firstRow.y;
	data[2][0] = firstRow.z;
	data[3][0] = -Vec3<T>::Dot(b, t);

	data[0][1] = secondRow.x;
	data[1][1] = secondRow.y;
	data[2][1] = secondRow.z;
	data[3][1] = -Vec3<T>::Dot(a, t);

	data[0][2] = thirdRow.x;
	data[1][2] = thirdRow.y;
	data[2][2] = thirdRow.z;
	data[3][2] = -Vec3<T>::Dot(d, s);

	data[0][3] = fourthRow.x;
	data[1][3] = fourthRow.y;
	data[2][3] = fourthRow.z;
	data[3][3] = -Vec3<T>::Dot(c, s);

	return *this;
}

template <typename T>
Mat4<T> Mat4<T>::Transposed() const
{
	return Mat4<T>(data[0][0], data[0][1], data[0][2], data[0][3],
					data[1][0], data[1][1], data[1][2], data[1][3],
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]);
}

template <typename T>
Mat4<T>& Mat4<T>::Transpose()
{
	Mat4<T> temp = *this;

	data[0][1] = temp.data[1][0];
	data[0][2] = temp.data[2][0];
	data[0][3] = temp.data[3][0];

	data[1][0] = temp.data[0][1];
	data[1][2] = temp.data[2][1];
	data[1][3] = temp.data[3][1];

	data[2][0] = temp.data[0][2];
	data[2][1] = temp.data[1][2];
	data[2][3] = temp.data[3][2];

	data[3][0] = temp.data[0][3];
	data[3][1] = temp.data[1][3];
	data[3][2] = temp.data[2][3];

	return *this;
}

template <typename T>
float Mat4<T>::Determinant() const
{
	const Vec3<T> a = reinterpret_cast<const Vec3<T>&>(data[0]);
	const Vec3<T> b = reinterpret_cast<const Vec3<T>&>(data[1]);
	const Vec3<T> c = reinterpret_cast<const Vec3<T>&>(data[2]);
	const Vec3<T> d = reinterpret_cast<const Vec3<T>&>(data[3]);

	Vec3<T> s = Vec3<T>::Cross(a, b);
	Vec3<T> t = Vec3<T>::Cross(c, d);
	Vec3<T> u = a * data[1][3] - b * data[0][3];
	Vec3<T> v = c * data[3][3] - d * data[2][3];

	return Vec3<T>::Dot(s, v) - Vec3<T>::Dot(t, u);
}

template <typename T>
Vec4<T> Mat4<T>::GetColumn(const int columnIndex) const
{
	return columns[columnIndex];
}

template <typename T>
void Mat4<T>::SetColumn(const int columnIndex, const Vec4<T>& vector)
{
	columns[columnIndex] = vector;
}

template <typename T>
Vec4<T> Mat4<T>::GetRow(const int rowIndex) const
{
	return Vec4<T>(data[0][rowIndex], 
					data[1][rowIndex], 
					data[2][rowIndex], 
					data[3][rowIndex]);
}

template <typename T>
void Mat4<T>::SetRow(const int rowIndex, const Vec4<T>& vector)
{
	data[0][rowIndex] = vector.x;
	data[1][rowIndex] = vector.y;
	data[2][rowIndex] = vector.z;
	data[3][rowIndex] = vector.w;
}

template <typename T>
Vec3<T> Mat4<T>::GetTranslation() const
{
	return columns[3];
}

template <typename T>
void Mat4<T>::SetTranslation(const Vec3<T>& translation)
{
	columns[3] = translation;
}

template <typename T>
Mat3<T> Mat4<T>::AffineMatrix() const
{
	return Mat3<T>(data[0][0], data[1][0], data[2][0],
					data[0][1], data[1][1], data[2][1], 
					data[0][2], data[1][2], data[2][2]);
}

template <typename T>
Mat3<T> Mat4<T>::NormalMatrix() const
{
	return AffineMatrix().Inverted().Transposed();
}

template <typename T>
Mat4<T> Mat4<T>::MakeRotationX(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat4<T>(1, 0, 0, 0,
					0, cos, -sin, 0,
					0, sin, cos, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeRotationY(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat4<T>(cos, 0, sin, 0,
					0, 1, 0, 0,
					-sin, 0, cos, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeRotationZ(const T angleInDegrees)
{
	T radians = DegreesToRad(angleInDegrees);
	T cos = std::cos(radians);
	T sin = std::sin(radians);

	return Mat4<T>(cos, -sin, 0, 0,
					sin, cos, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeRotation(const Vec3<T>& axis, const T angleInDegrees)
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

	return Mat4<T>(cos + x * axis.x, axisXAxisY - sin * axis.z, axisXAxisZ + sin * axis.y, 0,
					axisXAxisY + sin * axis.z, cos + y * axis.y, axisYAxisZ - sin * axis.x, 0,
					axisXAxisZ - sin * axis.y, axisYAxisZ + sin * axis.x, cos + z * axis.z, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeScale(const T uniformScale)
{
	return Mat4<T>(uniformScale, 0, 0, 0,
					0, uniformScale, 0, 0,
					0, 0, uniformScale, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeScale(const T scaleX, const T scaleY, const T scaleZ)
{
	return Mat4<T>(scaleX, 0, 0, 0,
					0, scaleY, 0, 0,
					0, 0, scaleZ, 0,
					0, 0, 0, 1);		
}

template <typename T>
Mat4<T> Mat4<T>::MakeScale(const Vec3<T>& vector)
{
	return Mat4<T>(vector.x, 0, 0, 0,
					0, vector.y, 0, 0,
					0, 0, vector.z, 0,
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::MakeTranslation(const T uniformTranslation)
{
	return Mat4<T>(1, 0, 0, uniformTranslation,
					0, 1, 0, uniformTranslation,
					0, 0, 1, uniformTranslation,
					0, 0, 0, 1);	
}

template <typename T>
Mat4<T> Mat4<T>::MakeTranslation(const T translationX, const T translationY, const T translationZ)
{
	return Mat4<T>(1, 0, 0, translationX,
					0, 1, 0, translationY,
					0, 0, 1, translationZ,
					0, 0, 0, 1);			
}

template <typename T>
Mat4<T> Mat4<T>::MakeTranslation(const Vec3<T>& vector)
{
	return Mat4<T>(1, 0, 0, vector.x,
					0, 1, 0, vector.y,
					0, 0, 1, vector.z,
					0, 0, 0, 1);	
}

template <typename T>
Mat4<T> Mat4<T>::LookAt(const Vec3<T>& cameraPosition, const Vec3<T>& targetPosition, const Vec3<T>& up)
{
	Vec3<T> forwardAxis = (cameraPosition - targetPosition).Normalize();
	Vec3<T> rightAxis = Vec3<T>::Cross(up, forwardAxis).Normalize();
	Vec3<T> upAxis = Vec3<T>::Cross(forwardAxis, rightAxis).Normalize();
			
	return Mat4<T>(rightAxis.x, rightAxis.y, rightAxis.z, -Vec3<T>::Dot(rightAxis, cameraPosition),
					upAxis.x, upAxis.y, upAxis.z, -Vec3<T>::Dot(upAxis, cameraPosition),
					forwardAxis.x, forwardAxis.y, forwardAxis.z, -Vec3<T>::Dot(forwardAxis, cameraPosition),
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::Orthographic(const T left, const T right, const T bottom, const T top, const T near, const T far)
{
	return Mat4<T>(static_cast<T>(2) / (right - left), 0, 0, (left + right) / (left - right),
					0, static_cast<T>(2) / (top - bottom), 0, (bottom + top) / (bottom - top),
					0, 0, static_cast<T>(2) / (near - far), (near + far) / (far - near),
					0, 0, 0, 1);
}

template <typename T>
Mat4<T> Mat4<T>::Perspective(const T fieldOfViewInDegrees, const T aspectRatio, const T near, const T far)
{
	T c = static_cast<T>(1) / std::tan(fieldOfViewInDegrees / static_cast<T>(2));
	T farMinusNear = far - near;

	return Mat4<T>(c / aspectRatio, 0, 0, 0,
					0, c, 0, 0,
					0, 0, static_cast<T>(-1) * (far + near) / (farMinusNear), static_cast<T>(-2) * far * near / farMinusNear,
					0, 0, -1, 0);
}

template <typename T>
Mat4<T> Mat4<T>::Identity()
{
	return Mat4<T>(1);
}

template <typename T>
Mat4<T>& Mat4<T>::operator=(const Mat4<T>& matrix)
{
	std::memcpy(data, matrix.data, sizeof(Mat4<T>));
	return *this;
}

template<typename T>
const T& Mat4<T>::operator()(const int rowIndex, const int columnIndex) const
{
	return data[columnIndex][rowIndex];
}

template<typename T>
T& Mat4<T>::operator()(const int rowIndex, const int columnIndex)
{
	return data[columnIndex][rowIndex];
}

template <typename T>
Mat4<T>& Mat4<T>::operator*=(const Mat4<T>& matrix)
{
	Mat4<T> temp = *this;

	data[0][0] = temp.data[0][0] * matrix.data[0][0] + temp.data[1][0] * matrix.data[0][1] + temp.data[2][0] * matrix.data[0][2] + temp.data[3][0] * matrix.data[0][3];
	data[1][0] = temp.data[0][0] * matrix.data[1][0] + temp.data[1][0] * matrix.data[1][1] + temp.data[2][0] * matrix.data[1][2] + temp.data[3][0] * matrix.data[1][3];
	data[2][0] = temp.data[0][0] * matrix.data[2][0] + temp.data[1][0] * matrix.data[2][1] + temp.data[2][0] * matrix.data[2][2] + temp.data[3][0] * matrix.data[2][3];
	data[3][0] = temp.data[0][0] * matrix.data[3][0] + temp.data[1][0] * matrix.data[3][1] + temp.data[2][0] * matrix.data[3][2] + temp.data[3][0] * matrix.data[3][3];

	data[0][1] = temp.data[0][1] * matrix.data[0][0] + temp.data[1][1] * matrix.data[0][1] + temp.data[2][1] * matrix.data[0][2] + temp.data[3][1] * matrix.data[0][3];
	data[1][1] = temp.data[0][1] * matrix.data[1][0] + temp.data[1][1] * matrix.data[1][1] + temp.data[2][1] * matrix.data[1][2] + temp.data[3][1] * matrix.data[1][3];
	data[2][1] = temp.data[0][1] * matrix.data[2][0] + temp.data[1][1] * matrix.data[2][1] + temp.data[2][1] * matrix.data[2][2] + temp.data[3][1] * matrix.data[2][3];
	data[3][1] = temp.data[0][1] * matrix.data[3][0] + temp.data[1][1] * matrix.data[3][1] + temp.data[2][1] * matrix.data[3][2] + temp.data[3][1] * matrix.data[3][3];

	data[0][2] = temp.data[0][2] * matrix.data[0][0] + temp.data[1][2] * matrix.data[0][1] + temp.data[2][2] * matrix.data[0][2] + temp.data[3][2] * matrix.data[0][3];
	data[1][2] = temp.data[0][2] * matrix.data[1][0] + temp.data[1][2] * matrix.data[1][1] + temp.data[2][2] * matrix.data[1][2] + temp.data[3][2] * matrix.data[1][3];
	data[2][2] = temp.data[0][2] * matrix.data[2][0] + temp.data[1][2] * matrix.data[2][1] + temp.data[2][2] * matrix.data[2][2] + temp.data[3][2] * matrix.data[2][3];
	data[3][2] = temp.data[0][2] * matrix.data[3][0] + temp.data[1][2] * matrix.data[3][1] + temp.data[2][2] * matrix.data[3][2] + temp.data[3][2] * matrix.data[3][3];

	data[0][3] = temp.data[0][3] * matrix.data[0][0] + temp.data[1][3] * matrix.data[0][1] + temp.data[2][3] * matrix.data[0][2] + temp.data[3][3] * matrix.data[0][3];
	data[1][3] = temp.data[0][3] * matrix.data[1][0] + temp.data[1][3] * matrix.data[1][1] + temp.data[2][3] * matrix.data[1][2] + temp.data[3][3] * matrix.data[1][3];
	data[2][3] = temp.data[0][3] * matrix.data[2][0] + temp.data[1][3] * matrix.data[2][1] + temp.data[2][3] * matrix.data[2][2] + temp.data[3][3] * matrix.data[2][3];
	data[3][3] = temp.data[0][3] * matrix.data[3][0] + temp.data[1][3] * matrix.data[3][1] + temp.data[2][3] * matrix.data[3][2] + temp.data[3][3] * matrix.data[3][3];

	return *this;
}

template <typename T>
Mat4<T>& Mat4<T>::operator*=(const T scalar)
{
	columns[0] *= scalar;
	columns[1] *= scalar;
	columns[2] *= scalar;
	columns[3] *= scalar;

	return *this;
}

template <typename T>
Mat4<T> operator*(const Mat4<T>& leftMatrix, const Mat4<T>& rightMatrix)
{
	Mat4<T> leftMatrixCopy = leftMatrix;
	return leftMatrixCopy *= rightMatrix;
}

template <typename T>
Vec4<T> operator*(const Mat4<T>& matrix, const Vec4<T>& vector)
{
	return Vec4<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
					matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
					matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
					matrix(0, 3) * vector.x + matrix(1, 3) * vector.y + matrix(2, 3) * vector.z + matrix(3, 3) * vector.w);
}

template <typename T>
Mat4<T> operator*(const Mat4<T>& matrix, const T scalar)
{
	Mat4<T> matrixCopy = matrix;
	return matrixCopy *= scalar;
}

template<typename T>
Mat4<T> operator*(const T scalar, const Mat4<T>& matrix)
{
	Mat4<T> matrixCopy = matrix;
	return matrixCopy *= scalar;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Mat4<T>& matrix)
{
	stream << "( " << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << std::endl;
	stream << "  " << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << std::endl;
	stream << "  " << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << std::endl;
	stream << "  " << matrix(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << " )";
	return stream;
}
