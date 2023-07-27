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

		OBB(Vector2 points[4]);
		OBB(Vector2 points[4], D2D1::Matrix3x2F matrix);

		void Transform(D2D1::Matrix3x2F matrix);

		Vector2 mPoints[4];
	};
}