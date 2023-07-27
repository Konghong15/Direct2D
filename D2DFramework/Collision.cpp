#include <limits>

#include "AABB.h"
#include "Collision.h"
#include "ColliderInfo.h"
#include "OBB.h"
#include "Circle.h"

namespace d2dFramework
{
	bool Collision::CheckAABBToAABB(const AABB& lhs, const AABB& rhs)
	{
		bool result = (lhs.left < rhs.right &&
			rhs.left < lhs.right &&
			lhs.top < rhs.bottom &&
			rhs.top < lhs.bottom);

		return lhs.top < lhs.bottom ? result : !result;
	}

	bool Collision::CheckAABBToOBB(const AABB& lhs, const OBB& rhs)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 rectangle[VERTEX_COUNT] =
		{
			{ lhs.left, lhs.top },
			{ lhs.right, lhs.top },
			{ lhs.right, lhs.bottom },
			{ lhs.left, lhs.bottom }
		};
		Vector2 normalVectors[VERTEX_COUNT] =
		{
			{ 0, 1 },
			{ 0, -1 },
			{ 1, 0 },
			{ -1, 0 }
		};

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			float rectMin = FLT_MAX;
			float rectMax = -FLT_MAX;

			for (int j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], rectangle[j]);

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float otherRectMin = FLT_MAX;
			float otherRectMax = -FLT_MAX;

			for (size_t j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], rhs.mPoints[j]);

				if (otherRectMax < scalar)
				{
					otherRectMax = scalar;
				}
				if (otherRectMin > scalar)
				{
					otherRectMin = scalar;
				}
			}

			if (otherRectMax < rectMin || rectMax < otherRectMin)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckAABBToCircle(const AABB& lhs, const Circle& rhs)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 rectangle[VERTEX_COUNT] =
		{
			{ lhs.left, lhs.top },
			{ lhs.right, lhs.top },
			{ lhs.right, lhs.bottom },
			{ lhs.left, lhs.bottom }
		};
		Vector2 normalVectors[VERTEX_COUNT] =
		{
			{ 0, 1 },
			{ 0, -1 },
			{ 1, 0 },
			{ -1, 0 }
		};

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			float rectMin = FLT_MAX;
			float rectMax = -FLT_MAX;

			for (int j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], rectangle[j]);

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float scalar = Vector2::Dot(normalVectors[i], rhs.Center);

			float circleMin = scalar - rhs.Radius;
			float circleMax = scalar + rhs.Radius;

			if (circleMax < rectMin || circleMin > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckOBBToOBB(const OBB& lhs, const OBB& rhs)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 normalVectors[VERTEX_COUNT];

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			normalVectors[i] = lhs.mPoints[i % VERTEX_COUNT] - lhs.mPoints[(i + 1) % VERTEX_COUNT];
			normalVectors->Normalize();
			normalVectors[i] = { -normalVectors[i].GetY(), normalVectors[i].GetX() };
		}

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			float rectMin = FLT_MAX;
			float rectMax = -FLT_MAX;

			for (int j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], lhs.mPoints[j]);

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float otherRectMin = FLT_MAX;
			float otherRectMax = -FLT_MAX;

			for (size_t j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], rhs.mPoints[j]);

				if (otherRectMax < scalar)
				{
					otherRectMax = scalar;
				}
				if (otherRectMin > scalar)
				{
					otherRectMin = scalar;
				}
			}

			if (otherRectMax < rectMin || rectMax < otherRectMin)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckOBBToCircle(const OBB& lhs, const Circle& rhs)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 normalVectors[VERTEX_COUNT];

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			normalVectors[i] = lhs.mPoints[i % VERTEX_COUNT] - lhs.mPoints[(i + 1) % VERTEX_COUNT];
			normalVectors->Normalize();
			normalVectors[i] = { -normalVectors[i].GetY(), normalVectors[i].GetX() };
		}

		for (size_t i = 0; i < VERTEX_COUNT; ++i)
		{
			float rectMin = FLT_MAX;
			float rectMax = -FLT_MAX;

			for (int j = 0; j < VERTEX_COUNT; ++j)
			{
				float scalar = Vector2::Dot(normalVectors[i], lhs.mPoints[j]);

				if (rectMax < scalar)
				{
					rectMax = scalar;
				}
				if (rectMin > scalar)
				{
					rectMin = scalar;
				}
			}

			float scalar = Vector2::Dot(normalVectors[i], rhs.Center);

			float circleMin = scalar - rhs.Radius;
			float circleMax = scalar + rhs.Radius;

			if (circleMax < rectMin || circleMin > rectMax)
			{
				return false;
			}
		}

		return true;
	}

	bool Collision::CheckCircleToCircle(const Circle& lhs, const Circle& rhs)
	{
		return Vector2::GetDistance(lhs.Center, rhs.Center) < lhs.Radius + rhs.Radius;
	}

	AABB Collision::MakeAABB(const ColliderInfo& colliderInfo)
	{
		AABB aabb(colliderInfo.Size.GetX() * -0.5f,
			colliderInfo.Size.GetY() * -0.5f,
			colliderInfo.Size.GetX() * 0.5f,
			colliderInfo.Size.GetY() * 0.5f);

		aabb.Scale(colliderInfo.Scale);
		aabb.Translate(colliderInfo.Translate + colliderInfo.Offset);

		return aabb;
	}

	OBB Collision::MakeOBB(const ColliderInfo& colliderInfo)
	{
		const Vector2 TL{ colliderInfo.Size.GetX() * -0.5f, colliderInfo.Size.GetY() * -0.5f };
		const Vector2 BR{ colliderInfo.Size.GetX() * 0.5f, colliderInfo.Size.GetY() * 0.5f };

		Vector2 points[4] =
		{
			TL,
			{ BR.GetX(), TL.GetY() }, // TR
			BR,
			{ TL.GetX(), BR.GetY() } // BL
		};

		D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Scale({ colliderInfo.Scale.GetX(), colliderInfo.Scale.GetY() }) * D2D1::Matrix3x2F::Rotation(colliderInfo.RotateInRadian) * D2D1::Matrix3x2F::Translation({ colliderInfo.Translate.GetX() + colliderInfo.Offset.GetX(), colliderInfo.Translate.GetY() + colliderInfo.Offset.GetY() });

		return OBB(points, matrix);
	}

	Circle Collision::MakeCircle(const ColliderInfo& colliderInfo)
	{
		float radius = colliderInfo.Size.GetX() > colliderInfo.Size.GetY() ? colliderInfo.Size.GetX() : colliderInfo.Size.GetY();
		Circle circle({ 0,0 }, radius);

		float scale = colliderInfo.Scale.GetX() > colliderInfo.Scale.GetY() ? colliderInfo.Scale.GetX() : colliderInfo.Scale.GetY();
		circle.Scale(scale);
		circle.Translate(colliderInfo.Translate);

		return circle;
	}
}