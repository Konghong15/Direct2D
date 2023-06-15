#include <cmath>

#include "Collision.h"
#include "Vector2.h"
#include "Circle.h"
#include "hRectangle.h"

#define FLT_EPSILON (0.001f)

namespace gameProcessor
{
	bool Collision::CheckPointToRectangle(const Vector2& point, const hRectangle& rectangle)
	{
		// poin
		return true;
	}

	bool Collision::CheckPointToRadius(const Vector2& point, const Circle& circle)
	{
		float diff = Vector2::GetDistance(point, circle.GetCenter());

		return circle.GetRadius() - diff < 0.f;
	}
}