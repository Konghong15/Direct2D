#pragma once

#include "Vector2.h"

namespace d2dFramework
{
	struct OBB
	{
		Vector2 mPoints[4];
		float RotateInRadian;
	};
}