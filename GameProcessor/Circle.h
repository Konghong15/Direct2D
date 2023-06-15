#pragma once

#include "Vector2.h"

namespace gameProcessor
{
	class Circle
	{
	public:
		Circle(const Vector2& center, float radius);

		void Transform();
		void Scale();
		void Translate();
		void Rotate();

		void Move(float x, float y);
		void Move(const Vector2& vector);
		void SetRadius(float radius);

		inline const Vector2& GetCenter() const;
		inline float GetRadius() const;

	private:
		Vector2 mCenter;
		float mRadius;
	};
}