#pragma once

#include "Vector2.h"

namespace d2dFramework
{
	enum class eColliderType
	{
		AABB,
		OBB,
		Circle
	};

	struct ColliderInfo
	{
		eColliderType ColliderType;
		Vector2 Size;
		Vector2 Offset;
		Vector2 Scale;
		float RotateInRadian;
		Vector2 Translate;
	};
}
