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
		Vector2 Size; // 너비 높이
		Vector2 Offset;
		Vector2 Scale; // 스케일 값
		float RotateInDegree;
		Vector2 Translate; // 중심 좌표
		bool bIsCollision;
	};
}
