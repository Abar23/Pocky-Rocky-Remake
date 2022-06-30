#pragma once

#include <array>
#include <ostream>

template <template <typename> class vectorType, typename T, int numberOfElements, int... Indices>
class Swizzle
{
private:
	std::array<T, numberOfElements> data;

public:
	vectorType<T>& operator=(const vectorType<T>& vector)
	{
		T indices[sizeof...(Indices)] = {Indices...};

		for (unsigned int i = 0; i < this->data.size(); i++)
		{
			this->data[indices[i]] = vector[i];
		}

		return *(vectorType<T>*)this;
	}

	unsigned int NumberOfBytes()
	{
		return sizeof...(Indices) * sizeof(T);
	}

	unsigned int NumberOfElements()
	{
		return sizeof...(Indices);
	}

	inline operator vectorType<T>() const
	{
		return vectorType<T>(data[Indices]...);
	}

	inline vectorType<T>& operator+=(const vectorType<T>& vector)
	{
		return *(reinterpret_cast<vectorType<T>*>(this)) += vector;
	}

	inline vectorType<T>& operator-=(const vectorType<T>& vector)
	{
		return *(reinterpret_cast<vectorType<T>*>(this)) -= vector;
	}

	inline vectorType<T>& operator*=(const T scalar)
	{
		return *(reinterpret_cast<vectorType<T>*>(this)) *= scalar;
	}

	inline vectorType<T>& operator/=(const T scalar)
	{
		return *(reinterpret_cast<vectorType<T>*>(this)) /= scalar;
	}

	friend vectorType<T> operator+(const Swizzle& leftSwizzle, const Swizzle& rightSwizzle)
	{
		vectorType<T> leftSwizzleCopy = leftSwizzle;
		return leftSwizzleCopy += rightSwizzle;
	}

	friend vectorType<T> operator-(const Swizzle& leftSwizzle, const Swizzle& rightSwizzle)
	{
		vectorType<T> leftSwizzleCopy = leftSwizzle;
		return leftSwizzleCopy -= rightSwizzle;
	}

	friend vectorType<T> operator*(const Swizzle& leftSwizzle, const T scalar)
	{
		vectorType<T> leftSwizzleCopy = leftSwizzle;
		return leftSwizzleCopy *= scalar;
	}

	friend vectorType<T> operator/(const Swizzle& leftSwizzle, const T scalar)
	{
		vectorType<T> leftSwizzleCopy = leftSwizzle;
		return leftSwizzleCopy /= scalar;
	}

	friend std::ostream& operator<<(std::ostream& stream, Swizzle& swizzle)
	{
		stream << static_cast<vectorType<T>>(swizzle);
		return stream;
	}
};