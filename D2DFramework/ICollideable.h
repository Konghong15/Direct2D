#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class hRectangle;
	struct ColliderInfo;

	class ICollideable : public IBaseInterface
	{
	public:
		ICollideable();
		virtual ~ICollideable();

		virtual void UpdateColliderInfo() = 0;
		virtual void CheckCollision(ICollideable* other) = 0;
		virtual void OnCollision() = 0;
		virtual inline const ColliderInfo& GetColliderInfo() const = 0;
	};
}