#pragma once

#include "Vector2.h"

namespace d2dFramework
{
	struct OBB
	{
		OBB();
		~OBB() = default;
		OBB(const OBB&) = default;
		OBB& operator=(const OBB&) = default;

		OBB(Vector2 points[4], float RotateInRadian);
		OBB(Vector2 points[4], D2D1::Matrix3x2F matrix, float RotateInRadian);

		void Transform(D2D1::Matrix3x2F matrix);

		inline Vector2 GetCenter() const;
		inline Vector2 GetSize() const;

		Vector2 mPoints[4];
		float RotateInRadian;
	};

	Vector2 OBB::GetCenter() const
	{
		return (mPoints[0] + mPoints[2]) * 0.5f;
	}

	Vector2 OBB::GetSize() const
	{
		Vector2 result =
		{
			Vector2::GetDistance(mPoints[0], mPoints[1]),
			Vector2::GetDistance(mPoints[1], mPoints[2])
		};

		return result;
	}
}