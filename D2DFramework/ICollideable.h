#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class hRectangle;
	class ColliderInfo;

	class ICollideable : public IBaseInterface
	{
	public:
		ICollideable();
		virtual ~ICollideable();

		virtual void UpdateColliderInfo() = 0;
		virtual void CheckCollision(ICollideable* other) = 0;
		virtual inline const ColliderInfo& GetColliderInfo() = 0;
	};
}