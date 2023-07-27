#pragma once

#include <d2d1.h>

namespace d2dFramework
{
	class Vector2;

	struct AABB : public D2D1_RECT_F
	{
		AABB();
		~AABB() = default;
		AABB(const AABB&) = default;
		AABB& operator=(const AABB&) = default;

		AABB(float left, float top, float right, float bottom);

		void Translate(const Vector2& tanslate);
		void Scale(const Vector2& tanslate);
		void Scale(float scalar);
	};
}