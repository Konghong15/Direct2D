#pragma once

namespace d2dFramework
{
	struct AABB;
	struct OBB;
	struct Circle;
	struct ColliderInfo;

	class Collision
	{
	public:
		static bool CheckAABBToAABB(const AABB& lhs, const AABB& rhs);
		static bool CheckAABBToOBB(const AABB& lhs, const OBB& rhs);
		static bool CheckAABBToCircle(const AABB& lhs, const Circle& rhs);

		static bool CheckOBBToOBB(const OBB& lhs, const OBB& rhs);
		static bool CheckOBBToCircle(const OBB& lhs, const Circle& rhs);
		
		static bool CheckCircleToCircle(const Circle& lhs, const Circle& rhs);

		static AABB MakeAABB(const ColliderInfo& colliderInfo);
		static OBB MakeOBB(const ColliderInfo& colliderInfo);
		static Circle MakeCircle(const ColliderInfo& colliderInfo);
	};
}