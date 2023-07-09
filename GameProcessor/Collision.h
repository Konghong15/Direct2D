#pragma once

namespace gameProcessor
{
	class Vector2;
	class hRectangle;
	class Circle;

	class Collision
	{
	public:
		static bool CheckPointToRectangle(const Vector2& point, const hRectangle& rectangle);
		static bool CheckPointToCircle(const Vector2& point, const Circle& circle);
		static bool CheckLineToRectangle(const Vector2& start, const Vector2& end, const hRectangle& rectangle);
		static bool CheckCircleToRectangle(const Circle& circle, const hRectangle& rectangle);
		static bool CheckCircleToCircle(const Circle& lhs, const Circle& rhs);
		static bool CheckRectangleToRectangle(const hRectangle& rectangle1, const hRectangle& rectangle2);
		static bool ContainRectangleToRectangle(const hRectangle& rectangle1, const hRectangle& rectangle2);
	};
}