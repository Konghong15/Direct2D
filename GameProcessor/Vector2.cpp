#include <cmath>
#include <limits>

#include "Vector2.h"

#ifndef EPSILON
#define EPSILON (0.001f)
#endif 

namespace gameProcessor
{
	Vector2::Vector2(float x, float y)
		: mX(x)
		, mY(y)
	{
	}

	Vector2::Vector2()
		: Vector2(0.f, 0.f)
	{
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return fabs(mX - other.mX) < EPSILON && fabs(mY - other.mY) < EPSILON;
	}

	bool Vector2::operator!=(const Vector2& other) const
	{
		return fabs(mX - other.mX) > EPSILON || fabs(mY - other.mY) > EPSILON;
	}

	float Vector2::GetDistance(const Vector2& vector, const Vector2& otherVector)
	{
		float x = abs(vector.mX - otherVector.mX);
		float y = abs(vector.mY - otherVector.mY);

		return sqrtf(x * x + y * y);
	}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(mX + other.mX, mY + other.mY);
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(mX - other.mX, mY - other.mY);
	}

	float Vector2::GetMagnitude() const
	{
		return sqrt(mX * mX + mY * mY);
	}

	float Vector2::Dot(const Vector2& other)
	{
		return mX * other.mX + mY * other.mY;
	}

	void Vector2::Normalize()
	{
		float magnitude = GetMagnitude();

		mX /= magnitude;
		mY /= magnitude;
	}
}

