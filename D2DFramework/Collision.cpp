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
		Vector2 diffVec = GetCenter(rhs) - GetCenter(lhs);

		const float LHS_HALF_X = GetWidth(lhs) * 0.5f;
		const float LHS_HALF_Y = GetHeight(lhs) * 0.5f;
		const float RHS_HALF_X = GetWidth(rhs) * 0.5f;
		const float RHS_HALF_Y = GetHeight(rhs) * 0.5f;

		const float X_OVERLAP = LHS_HALF_X + RHS_HALF_X - fabsf(diffVec.GetX());
		const float Y_OVERLAP = LHS_HALF_Y + RHS_HALF_Y - fabsf(diffVec.GetY());

		if (X_OVERLAP < 0 || Y_OVERLAP < 0)
		{
			return false;
		}

		if (X_OVERLAP > Y_OVERLAP)
		{
			if (diffVec.GetY() < 0)
			{
				outmanifold->CollisionNormal = Vector2(0, -1);
			}
			else
			{
				outmanifold->CollisionNormal = Vector2(0, 1);
			}
			outmanifold->Penetration = Y_OVERLAP;
		}
		else
		{
			if (diffVec.GetX() < 0)
			{
				outmanifold->CollisionNormal = Vector2(-1, 0);
			}
			else
			{
				outmanifold->CollisionNormal = Vector2(1, 0);
			}
			outmanifold->Penetration = X_OVERLAP;
		}

		return true;
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

		Vector2 diffVec = rhs.Center - GetCenter(lhs);
		Vector2 closet =
		{
			MathHelper::Clamp(diffVec.GetX(), -RECT_HALF_WIDTH, RECT_HALF_WIDTH),
			MathHelper::Clamp(diffVec.GetY(), -RECT_HALF_HEIGHT, RECT_HALF_HEIGHT)
		};

		bool inside = closet == diffVec;

		Vector2 normal = diffVec - closet;
		float normalLengthSquard = normal.GetMagnitudeSquared();
		float radiusSquard = rhs.Radius * rhs.Radius;

		if (normalLengthSquard > radiusSquard && !inside)
		{
			return false;
		}

		outmanifold->Penetration = rhs.Radius - sqrt(normalLengthSquard);
		normal.Normalize();

		if (inside)
		{
			outmanifold->CollisionNormal = normal * -1;
		}
		else
		{
			outmanifold->CollisionNormal = normal;
		}

		return true;
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

	bool Collision::CheckCircleToAABB(const Circle& lhs, const AABB& rhs, Manifold* outManifold)
	{
		bool result = CheckAABBToCircle(rhs, lhs, outManifold);

		outManifold->CollisionNormal *= -1.f;

		return result;
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