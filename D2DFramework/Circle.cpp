#include "Circle.h"

namespace d2dFramework
{
	Circle::Circle()
		: Circle({ 0.f, 0.f }, 0.f)
	{
	}

	Circle::Circle(Vector2 center, float radius)
		: Center(center)
		, Radius(radius)
	{
	}

	void Circle::Translate(const Vector2& translate)
	{
		Center.Move(translate.GetX(), translate.GetY());
	}

	void Circle::Scale(float scalar)
	{
		Radius* scalar;
	}
}