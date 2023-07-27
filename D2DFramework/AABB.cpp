#include "AABB.h"
#include "Vector2.h"

namespace d2dFramework
{
	AABB::AABB()
		: AABB(0.f, 0.f, 0.f, 0.f)
	{
	}

	AABB::AABB(float left, float top, float right, float bottom)
		: D2D1_RECT_F{ left, top, right, bottom }
	{
	}

	void AABB::Translate(const Vector2& tanslate)
	{
		left += tanslate.GetX();
		right += tanslate.GetX();
		top += tanslate.GetY();
		bottom += tanslate.GetY();
	}

	void AABB::Scale(const Vector2& scale)
	{
		left *= scale.GetX();
		right *= scale.GetX();
		top *= scale.GetY();
		bottom *= scale.GetY();
	}

	void AABB::Scale(float scalar)
	{
		left *= scalar;
		right *= scalar;
		top *= scalar;
		bottom *= scalar;
	}
}