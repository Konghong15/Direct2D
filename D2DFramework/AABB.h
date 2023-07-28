#pragma once

#include <d2d1.h>
#include "Vector2.h"

namespace d2dFramework
{
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

		inline float GetWidth() const;
		inline float GetHeight() const;
		inline Vector2 GetCenter() const;
	};

	float AABB::GetWidth() const
	{
		return right - left;
	}
	float AABB::GetHeight() const
	{
		return bottom - top;
	}
	Vector2 AABB::GetCenter() const
	{
		return { (right + left) * 0.5f, (bottom + top) * 0.5f };
	}
}