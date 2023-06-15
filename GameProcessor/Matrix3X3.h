#pragma once

namespace gameProcessor
{
	class Matrix3X3
	{
	public:
		Matrix3X3();
		~Matrix3X3() = default;
		Matrix3X3(const Matrix3X3& other);
		Matrix3X3& operator=(const Matrix3X3& other);

		static Matrix3X3 GetScale(float x, float y);
		static Matrix3X3 GetRotate(float radian);
		static Matrix3X3 GetTranslate(float x, float y);
		static Matrix3X3 ComineMatrix(size_t count, const Matrix3X3& ...);

		Matrix3X3& operator*(const Matrix3X3& other);
		Matrix3X3& operator-(const Matrix3X3& other);
		Matrix3X3& operator+(const Matrix3X3& other);

		void InitIdentity();
		void Transpose();

	private:
		float m[3][3];
	};
}