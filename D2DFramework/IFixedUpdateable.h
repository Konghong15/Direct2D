#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class IFixedUpdateable : public IBaseInterface
	{
	public:
		IFixedUpdateable();
		virtual ~IFixedUpdateable();

		virtual void FixedUpdate(float deltaTime) = 0;
	};
}