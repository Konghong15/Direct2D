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
		static bool CheckPointToRadius(const Vector2& point, const Circle& circle);
	};
}