#pragma once

#include <cassert>

namespace gameProcessor
{
	class Matrix3X3
	{
	public:
		Matrix3X3();
		~Matrix3X3() = default;
		Matrix3X3(const Matrix3X3& other) = default;
		Matrix3X3& operator=(const Matrix3X3& other) = default;

		Matrix3X3(float m[3][3]);

		static Matrix3X3 GetScale(float x, float y);
		static Matrix3X3 GetRotate(float radian);
		static Matrix3X3 GetTranslate(float x, float y);
		static Matrix3X3 ComineMatrix(size_t count, const Matrix3X3& ...);

		Matrix3X3 operator*(const Matrix3X3& other);
		Matrix3X3 operator-(const Matrix3X3& other);
		Matrix3X3 operator+(const Matrix3X3& other);
		Matrix3X3& operator*=(const Matrix3X3& other);
		Matrix3X3& operator-=(const Matrix3X3& other);
		Matrix3X3& operator+=(const Matrix3X3& other);

		void InitIdentity();
		void Transpose();

		inline float GetValue(unsigned int x, unsigned y);
		inline void SetValue(unsigned int x, unsigned int y, float value);


	private:
		float m[3][3];
	};

	float Matrix3X3::GetValue(unsigned int x, unsigned y)
	{
		assert(x < 3 && y < 3);

		return m[y][x];
	}

	void Matrix3X3::SetValue(unsigned int x, unsigned int y, float value)
	{
		assert(x < 3 && y < 3);

		m[y][x] = value;
	}
}