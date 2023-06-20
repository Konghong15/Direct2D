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
		Vector2 left = rectangle.GetTopLeft() - rectangle.GetBottomLeft();
		Vector2 top = rectangle.GetTopRight() - rectangle.GetTopLeft();

		left.Normalize();
		top.Normalize();
		
		float tempX = left.GetX();
		float tempY = left.GetY();
		left.SetX(-tempY);
		left.SetY(tempX);
		tempX = top.GetX();
		tempY = top.GetY();
		top.SetX(-tempY);
		top.SetY(tempX);

		float rectMin;
		float rectMax;

		float pointMin;
		float pointMax;

		

		for (const Vector)

		return true;
	}

	bool Collision::CheckPointToRadius(const Vector2& point, const Circle& circle)
	{
		float diff = Vector2::GetDistance(point, circle.GetCenter());

		return circle.GetRadius() - diff < 0.f;
	}
}