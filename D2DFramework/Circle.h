#pragma once

#include "Vector2.h"

namespace d2dFramework
{
	struct Circle
	{
		Circle();
		~Circle() = default;
		Circle(const Circle&) = default;
		Circle& operator=(const Circle&) = default;

		Circle(Vector2 center, float radius);

		void Translate(const Vector2& tanslate);
		void Scale(float scalar);

		Vector2 Center;
		float Radius;
	};
}