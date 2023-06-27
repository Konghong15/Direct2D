#pragma once

#include <cassert>
#include <cmath>

namespace gameProcessor
{
	class Vector2;

	class Matrix3X3
	{
	public:
		Matrix3X3();
		~Matrix3X3() = default;
		Matrix3X3(const Matrix3X3& other) = default;
		Matrix3X3& operator=(const Matrix3X3& other) = default;

		Matrix3X3(float m[3][3]);

		static Matrix3X3 Identity();
		static Matrix3X3 GetScale(float x, float y);
		static Matrix3X3 GetScale(const Vector2& scale);
		static Matrix3X3 GetRotate(float radian);
		static Matrix3X3 GetTranslate(float x, float y);
		static Matrix3X3 GetTranslate(const Vector2& translate);
		static Matrix3X3 ComineMatrix(size_t count, const Matrix3X3& ...);

		Matrix3X3 operator*(const Matrix3X3& other);
		Matrix3X3 operator-(const Matrix3X3& other);
		Matrix3X3 operator+(const Matrix3X3& other);
		Matrix3X3& operator*=(const Matrix3X3& other);
		Matrix3X3& operator-=(const Matrix3X3& other);
		Matrix3X3& operator+=(const Matrix3X3& other);

		void InitIdentity();
		void Transpose();

		inline void SetValue(unsigned int x, unsigned int y, float value);
		inline void SetScale(float x, float y);
		inline void SetRotateInRadian(float radian);
		inline void SetTranslate(float x, float y);
		inline void AddScale(float x, float y);
		inline void AddTranslate(float x, float y);

		inline float GetValue(unsigned int x, unsigned y) const;

	private:
		enum { ROW_LENGTH = 3 };
		enum { COL_LENGTH = 3 };

		float m[COL_LENGTH][ROW_LENGTH];
	};

	float Matrix3X3::GetValue(unsigned int x, unsigned y) const
	{
		assert(x < ROW_LENGTH&& y < COL_LENGTH);

		return m[y][x];
	}

	void Matrix3X3::SetValue(unsigned int x, unsigned int y, float value)
	{
		assert(x < ROW_LENGTH&& y < COL_LENGTH);

		m[y][x] = value;
	}

	void Matrix3X3::SetScale(float x, float y)
	{
		m[0][0] = x;
		m[1][1] = y;
	}

	void Matrix3X3::SetRotateInRadian(float radian)
	{
		float cosTheta = cosf(radian);
		float sinTheta = sinf(radian);

		m[0][0] = cosTheta;
		m[0][1] = sinTheta;
		m[1][0] = -sinTheta;
		m[1][1] = cosTheta;
	}

	void Matrix3X3::SetTranslate(float x, float y)
	{
		m[2][0] = x;
		m[2][1] = y;
	}

	void Matrix3X3::AddScale(float x, float y)
	{
		m[0][0] += x;
		m[1][1] += y;
	}

	void Matrix3X3::AddTranslate(float x, float y)
	{
		m[2][0] += x;
		m[2][1] += y;
	}
}