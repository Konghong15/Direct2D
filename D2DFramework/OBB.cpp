#include "OBB.h"

namespace d2dFramework
{
	OBB::OBB()
		: mPoints{ Vector2(), }
		, RotateInRadian(0.f)
	{
	}

	OBB::OBB(Vector2 points[4], float rotateInRadian)
		: RotateInRadian(rotateInRadian)
	{
		memcpy(mPoints, points, sizeof(Vector2) * 4);
	}

	OBB::OBB(Vector2 points[4], D2D1::Matrix3x2F matrix, float rotateInRadian)
		: OBB(points, rotateInRadian)
	{
		Transform(matrix);
	}

	void OBB::Transform(D2D1::Matrix3x2F matrix)
	{
		for (size_t i = 0u; i < 4u; ++i)
		{
			D2D1_POINT_2F point = matrix.TransformPoint({ mPoints[i].GetX(), mPoints[i].GetY() });

			mPoints[i].SetX(point.x);
			mPoints[i].SetY(point.y);
		}
	}
}