#include "Circle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	Circle::Circle(const Vector2& center, float radius)
		: mCenter(center)
		, mRadius(radius)
	{
	}

	Circle Circle::operator*(const Matrix3X3& matrix) const
	{
		Circle result(*this);
		result.mCenter.Move(matrix.GetValue(0, 2), matrix.GetValue(1, 2));

		return result;
	}

	Circle& Circle::operator*=(const Matrix3X3& matrix)
	{
		mCenter.Move(matrix.GetValue(0, 2), matrix.GetValue(1, 2));

		return *this;
	}
}