#pragma once

#include "Vector2.h"

namespace gameProcessor
{
	class Circle
	{
	public:
		Circle(const Vector2& center, float radius);

		inline void Scale(float scalar);
		inline void Move(float x, float y);
		inline void Move(const Vector2& vector);
		inline void SetRadius(float radius);

		inline const Vector2& GetCenter() const;
		inline float GetRadius() const;

	private:
		Vector2 mCenter;
		float mRadius;
	};

	void Circle::Scale(float scalar)
	{
		mRadius* scalar;
	}

	void Circle::Move(float x, float y)
	{
		mCenter.Move(x, y);
	}

	void Circle::Move(const Vector2& vector)
	{
		mCenter.Move(vector.GetX(), vector.GetY());
	}

	void Circle::SetRadius(float radius)
	{
		mRadius = radius;
	}

	const Vector2& Circle::GetCenter() const
	{
		return mCenter;
	}

	float Circle::GetRadius() const
	{
		return mRadius;
	}
}