#pragma once

#include <array>
#include <initializer_list>
#include "Vec4.h"
#include "Mat3.h"

template <typename T>
class Mat4
{
public:
	union
	{
		T data[4][4];

		Vec4<T> columns[4];
	};

	Mat4();
	Mat4(std::initializer_list<T> args);
	Mat4(const T m00, const T m01, const T m02, const T m03,
			const T m10, const T m11, const T m12, const T m13,
			const T m20, const T m21, const T m22, const T m23,
			const T m30, const T m31, const T m32, const T m33);
	Mat4(const Vec4<T>& firstRow,
			const Vec4<T>& secondRow,
			const Vec4<T>& thirdRow,
			const Vec4<T>& fourthRow);
	Mat4(const T diagonal);
	Mat4(const Mat4<T>& matrix);

	~Mat4() = default;

	Mat4<T> Inverted() const;
	Mat4<T>& Invert();
	Mat4<T> Transposed() const;
	Mat4<T>& Transpose();
	float Determinant() const;
	Vec4<T> GetColumn(const int columnIndex) const;
	void SetColumn(const int columnIndex, const Vec4<T>& vector);
	Vec4<T> GetRow(const int rowIndex) const;
	void SetRow(const int rowIndex, const Vec4<T>& vector);
	Vec3<T> GetTranslation() const;
	void SetTranslation(const Vec3<T>& translation);
	Mat3<T> AffineMatrix() const;
	Mat3<T> NormalMatrix() const;

	static Mat4<T> MakeRotationX(const T angleInDegrees);
	static Mat4<T> MakeRotationY(const T angleInDegrees);
	static Mat4<T> MakeRotationZ(const T angleInDegrees);
	static Mat4<T> MakeRotation(const Vec3<T>& axis, const T angleInDegrees);
	static Mat4<T> MakeScale(const T uniformScale);
	static Mat4<T> MakeScale(const T scaleX, const T scaleY, const T scaleZ);
	static Mat4<T> MakeScale(const Vec3<T>& vector);
	static Mat4<T> MakeTranslation(const T uniformTranslation);
	static Mat4<T> MakeTranslation(const T translationX, const T translationY, const T translationZ);
	static Mat4<T> MakeTranslation(const Vec3<T>& vector);
	static Mat4<T> LookAt(const Vec3<T>& cameraPosition, const Vec3<T>& targetPosition, const Vec3<T>& up);
	static Mat4<T> Orthographic(const T left, const T right, const T bottom , const T top, const T near, const T far);
	static Mat4<T> Perspective(const T fieldOfViewInDegrees, const T aspectRatio, const T near, const T far);
	static Mat4<T> Identity();

	Mat4<T>& operator=(const Mat4<T>& matrix);

	const T& operator()(const int rowIndex, const int columnIndex) const;
	T& operator()(const int rowIndex, const int columnIndex);

	Mat4<T>& operator*=(const Mat4<T>& matrix);
	Mat4<T>& operator*=(const T scalar);

	friend Vec4<T> operator*(const Mat4<T>& matrix, const Vec4<T>& vector)
	{
		return Vec4<T>(matrix(0, 0) * vector.x + matrix(1, 0) * vector.y + matrix(2, 0) * vector.z + matrix(3, 0) * vector.w,
						matrix(0, 1) * vector.x + matrix(1, 1) * vector.y + matrix(2, 1) * vector.z + matrix(3, 1) * vector.w,
						matrix(0, 2) * vector.x + matrix(1, 2) * vector.y + matrix(2, 2) * vector.z + matrix(3, 2) * vector.w,
						matrix(0, 3) * vector.x + matrix(1, 3) * vector.y + matrix(2, 3) * vector.z + matrix(3, 3) * vector.w);
	}
};

template <typename T>
Mat4<T> operator*(const Mat4<T>& leftMatrix, const Mat4<T>& rightMatrix);

template <typename T>
Mat4<T> operator*(const Mat4<T>& matrix, const T scalar);

template <typename T>
Mat4<T> operator*(const T scalar, const Mat4<T>& matrix);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Mat4<T>& matrix);

using mat4 = Mat4<float>;
using dmat4 = Mat4<double>;

#include "Mat4.inl"
