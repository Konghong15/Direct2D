#include <memory>
#include <stdarg.h>

#include "Matrix3X3.h"

namespace gameProcessor
{
	Matrix3X3::Matrix3X3()
		: m{ 0.f, }
	{
	}

	Matrix3X3::Matrix3X3(float m[3][3])
	{
		memcpy(this->m, m, 9 * sizeof(float));
	}

	Matrix3X3 Matrix3X3::GetScale(float x, float y)
	{
		float m[3][3] =
		{
			{x, 0, 0},
			{0, y, 0 },
			{0, 0, 1}
		};

		return Matrix3X3(m);
	}

	Matrix3X3 Matrix3X3::GetRotate(float radian)
	{
		Matrix3X3 result;
		result.InitIdentity();

		float cosTheta = cosf(radian);
		float sinTheta = sinf(radian);

		result.m[0][0] = cosTheta;
		result.m[0][1] = sinTheta;
		result.m[1][0] = -sinTheta;
		result.m[1][1] = cosTheta;

		return result;
	}

	Matrix3X3 Matrix3X3::GetTranslate(float x, float y)
	{
		Matrix3X3 result;
		result.InitIdentity();

		result.m[2][0] = x;
		result.m[2][1] = y;

		return result;
	}

	Matrix3X3 Matrix3X3::ComineMatrix(size_t count, const Matrix3X3& ...)
	{
		Matrix3X3 result;
		result.InitIdentity();

		va_list ap;
		va_start(ap, count);
		for (size_t i = 0; i < count; ++i)
		{
			const Matrix3X3& matrix = va_arg(ap, Matrix3X3);
			result *= matrix;
		}
		va_end(ap);

		return result;
	}


	Matrix3X3 Matrix3X3::operator*(const Matrix3X3& other)
	{
		Matrix3X3 result;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				result.m[i][j] =
					this->m[i][0] * other.m[0][j] +
					this->m[i][1] * other.m[1][j] +
					this->m[i][2] * other.m[2][j];
			}
		}

		return result;
	}

	Matrix3X3 Matrix3X3::operator-(const Matrix3X3& other)
	{
		Matrix3X3 result;

		for (int i = 0; i < 3; ++i)
		{
			result.m[i][0] = this->m[i][0] - other.m[i][0];
			result.m[i][0] = this->m[i][1] - other.m[i][1];
			result.m[i][0] = this->m[i][2] - other.m[i][2];
		}

		return result;
	}

	Matrix3X3 Matrix3X3::operator+(const Matrix3X3& other)
	{
		Matrix3X3 result;

		for (int i = 0; i < 3; ++i)
		{
			result.m[i][0] = this->m[i][0] + other.m[i][0];
			result.m[i][0] = this->m[i][1] + other.m[i][1];
			result.m[i][0] = this->m[i][2] + other.m[i][2];
		}

		return result;
	}

	Matrix3X3& Matrix3X3::operator*=(const Matrix3X3& other)
	{
		*this = (*this) * other;

		return *this;
	}

	Matrix3X3& Matrix3X3::operator-=(const Matrix3X3& other)
	{
		*this = (*this) - other;

		return *this;
	}

	Matrix3X3& Matrix3X3::operator+=(const Matrix3X3& other)
	{
		*this = (*this) + other;

		return *this;
	}

	void Matrix3X3::InitIdentity()
	{
		memset(this->m, 0, sizeof(float) * 9);

		m[0][0] = 1;
		m[1][1] = 1;
		m[2][2] = 1;
	}

	void Matrix3X3::Transpose()
	{
		float temp = m[0][1];
		m[0][1] = m[1][0];
		m[1][0] = temp;

		temp = m[0][2];
		m[0][2] = m[2][0];
		m[2][0] = temp;

		temp = m[1][2];
		m[1][2] = m[2][1];
		m[2][1] = temp;
	}
}