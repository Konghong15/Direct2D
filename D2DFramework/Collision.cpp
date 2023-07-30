#include <limits>
#include <cmath>

#include "AABB.h"
#include "Collision.h"
#include "OBB.h"
#include "Circle.h"
#include "MathHelper.h"
#include "Transform.h"
#include "Manifold.h"

namespace d2dFramework
{
	bool Collision::CheckAABBToAABB(const AABB& lhs, const AABB& rhs, Manifold* outmanifold)
	{
		if (lhs.TopLeft.GetY() < lhs.BottomRight.GetY())
		{
			return lhs.TopLeft.GetX() < rhs.BottomRight.GetX()
				&& rhs.TopLeft.GetX() < lhs.BottomRight.GetX()
				&& lhs.TopLeft.GetY() < rhs.BottomRight.GetY()
				&& rhs.TopLeft.GetY() < lhs.BottomRight.GetY();
		}
		else
		{
			return lhs.TopLeft.GetX() < rhs.BottomRight.GetX()
				&& rhs.TopLeft.GetX() < lhs.BottomRight.GetX()
				&& lhs.BottomRight.GetY() < rhs.TopLeft.GetY()
				&& rhs.BottomRight.GetY() < lhs.TopLeft.GetY();
		}
	}

	bool Collision::CheckAABBToOBB(const AABB& lhs, const OBB& rhs, Manifold* outmanifold)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 rectangle[VERTEX_COUNT] =
		{
			{ lhs.TopLeft },
			{ lhs.BottomRight.GetX(), lhs.TopLeft.GetY() },
			{ lhs.BottomRight },
			{ lhs.TopLeft.GetX(), lhs.BottomRight.GetY()  }
		};
		Vector2 normalVectors[VERTEX_COUNT] =
		{
			{ 0, 1 },
			{ 0, -1 },
		};

		for (size_t i = 2; i < 4; ++i)
		{
			normalVectors[i] = rhs.mPoints[i % VERTEX_COUNT] - rhs.mPoints[(i + 1) % VERTEX_COUNT];
			normalVectors->Normalize();
			normalVectors[i] = { -normalVectors[i].GetY(), normalVectors[i].GetX() };
		}


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

	bool Collision::CheckAABBToCircle(const AABB& lhs, const Circle& rhs, Manifold* outmanifold)
	{
		const float RECT_HALF_WIDTH = GetWidth(lhs) * 0.5f;
		const float RECT_HALF_HEIGHT = GetHeight(lhs) * 0.5f;

		const Vector2 RECT_CENTER = GetCenter(lhs);

		Vector2 distance = rhs.Center - RECT_CENTER;
		distance.AbsXY();

		if (distance.GetX() > RECT_HALF_WIDTH + rhs.Radius)
		{
			return false;
		}
		if (distance.GetY() > RECT_HALF_HEIGHT + rhs.Radius)
		{
			return false;
		}

		if (distance.GetX() <= RECT_HALF_WIDTH || distance.GetY() <= RECT_HALF_HEIGHT)
		{
			return true;
		}

		float cornerDistance = std::pow(distance.GetX() - RECT_HALF_WIDTH, 2) + std::pow(distance.GetY() - RECT_HALF_HEIGHT, 2);
		return cornerDistance <= std::pow(rhs.Radius, 2);
	}

	bool Collision::CheckOBBToOBB(const OBB& lhs, const OBB& rhs, Manifold* outmanifold)
	{
		const size_t VERTEX_COUNT = 4;
		Vector2 normalVectors[VERTEX_COUNT];

		for (size_t i = 0; i < 2; ++i)
		{
			normalVectors[i] = lhs.mPoints[i % VERTEX_COUNT] - lhs.mPoints[(i + 1) % VERTEX_COUNT];
			normalVectors->Normalize();
			normalVectors[i] = { -normalVectors[i].GetY(), normalVectors[i].GetX() };
		}

		for (size_t i = 2; i < 4; ++i)
		{
			normalVectors[i] = rhs.mPoints[i % VERTEX_COUNT] - rhs.mPoints[(i + 1) % VERTEX_COUNT];
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

	bool Collision::CheckOBBToCircle(const OBB& lhs, const Circle& rhs, Manifold* outmanifold)
	{
		const Vector2 RECT_HALF_SIZE = GetSize(lhs) * 0.5f;

		Vector2 distance = rhs.Center - GetCenter(lhs);
		distance.Rotate(lhs.RotateInRadian);
		distance.AbsXY();

		// 충돌 검출
		if (distance.GetX() > RECT_HALF_SIZE.GetX() + rhs.Radius) {
			return false;
		}
		if (distance.GetY() > RECT_HALF_SIZE.GetY() + rhs.Radius) {
			return false;
		}

		if (distance.GetX() <= RECT_HALF_SIZE.GetX() || distance.GetY() <= RECT_HALF_SIZE.GetY()) {
			return true;
		}

		// OBB의 꼭지점과 원의 중심 간의 거리 계산
		float cornerDistance = std::pow(distance.GetX() - RECT_HALF_SIZE.GetX(), 2) + std::pow(distance.GetY() - RECT_HALF_SIZE.GetY(), 2);
		float circleDistance = std::pow(rhs.Radius, 2);

		return cornerDistance <= circleDistance;
	}

	bool Collision::CheckCircleToCircle(const Circle& lhs, const Circle& rhs, Manifold* outmanifold)
	{
		Vector2 diffVec = rhs.Center - lhs.Center; // 언제나 lhs가 기준

		float distance = diffVec.GetMagnitude();
		float sumRadius = lhs.Radius + rhs.Radius;

		if (distance > sumRadius)
		{
			return false;
		}

		if (distance != 0)
		{
			outmanifold->Penetration = sumRadius - distance;
			outmanifold->CollisionNormal = diffVec / distance;
		}
		else // 중심이 완전이 같은 경우
		{
			outmanifold->Penetration = lhs.Radius;
			outmanifold->CollisionNormal = Vector2(1, 0);
		}

		return true;
	}

	float Collision::GetWidth(const AABB& aabb)
	{
		return aabb.BottomRight.GetX() - aabb.TopLeft.GetX();
	}
	float Collision::GetWidth(const OBB& obb)
	{
		return Vector2::GetDistance(obb.mPoints[0], obb.mPoints[1]);
	}

	float Collision::GetHeight(const AABB& aabb)
	{
		return fabs(aabb.BottomRight.GetY() - aabb.TopLeft.GetY());
	}
	float Collision::GetHeight(const OBB& obb)
	{
		return Vector2::GetDistance(obb.mPoints[1], obb.mPoints[2]);
	}

	Vector2 Collision::GetSize(const AABB& aabb)
	{
		return { GetWidth(aabb), GetHeight(aabb) };
	}
	Vector2 Collision::GetSize(const OBB& obb)
	{
		return { GetWidth(obb), GetHeight(obb) };
	}

	Vector2 Collision::GetCenter(const AABB& aabb)
	{
		Vector2 result =
		{
			(aabb.TopLeft.GetX() + aabb.BottomRight.GetX()) * 0.5f,
			(aabb.TopLeft.GetY() + aabb.BottomRight.GetY()) * 0.5f,
		};

		return result;
	}
	Vector2 Collision::GetCenter(const OBB& obb)
	{
		return (obb.mPoints[0] + obb.mPoints[2]) * 0.5f;
	}
}