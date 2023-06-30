#include <memory>
#include <stdarg.h>

#include "Matrix3X3.h"
#include "Vector2.h"

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

	Matrix3X3 Matrix3X3::Identity()
	{
		float m[3][3] =
		{
			{1, 0, 0},
			{0, 1, 0 },
			{0, 0, 1}
		};

		return Matrix3X3(m);
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

	Matrix3X3 Matrix3X3::GetScale(const Vector2& scale)
	{
		return GetScale(scale.GetX(), scale.GetY());
	}

	Matrix3X3 Matrix3X3::GetRotate(float radian)
	{
		float cosTheta = cosf(radian);
		float sinTheta = sinf(radian);

		float m[3][3] =
		{
			{cosTheta, sinTheta, 0},
			{-sinTheta, cosTheta, 0 },
			{0, 0, 1}
		};

		return Matrix3X3(m);
	}

	Matrix3X3 Matrix3X3::GetRotate(float cos, float sin)
	{
		float m[3][3] =
		{
			{cos, sin, 0},
			{-sin, cos, 0 },
			{0, 0, 1}
		};

		return Matrix3X3(m);
	}

	Matrix3X3 Matrix3X3::GetTranslate(float x, float y)
	{
		float m[3][3] =
		{
			{1, 0, 0},
			{0, 1, 0 },
			{x, y, 1}
		};

		return Matrix3X3(m);
	}

	Matrix3X3 Matrix3X3::GetTranslate(const gameProcessor::Vector2& vector)
	{
		return GetTranslate(vector.GetX(), vector.GetY());
	}

	bool Matrix3X3::TryInverse(const Matrix3X3& matrix, Matrix3X3* outMatrix)
	{
		float det = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) -
			matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) +
			matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);

		// 행렬식이 0인 경우 역행렬이 존재하지 않음
		if (det == 0) {
			return false;
		}

		// 역행렬 계산
		float invDet = 1.0 / det;

		outMatrix->m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * invDet;
		outMatrix->m[0][1] = (matrix.m[0][2] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][2]) * invDet;
		outMatrix->m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * invDet;
		outMatrix->m[1][0] = (matrix.m[1][2] * matrix.m[2][0] - matrix.m[1][0] * matrix.m[2][2]) * invDet;
		outMatrix->m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * invDet;
		outMatrix->m[1][2] = (matrix.m[0][2] * matrix.m[1][0] - matrix.m[0][0] * matrix.m[1][2]) * invDet;
		outMatrix->m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * invDet;
		outMatrix->m[2][1] = (matrix.m[0][1] * matrix.m[2][0] - matrix.m[0][0] * matrix.m[2][1]) * invDet;
		outMatrix->m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * invDet;

		return true;
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


	Matrix3X3 Matrix3X3::operator*(const Matrix3X3& other) const
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

	Matrix3X3 Matrix3X3::operator-(const Matrix3X3& other) const
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

	Matrix3X3 Matrix3X3::operator+(const Matrix3X3& other) const
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