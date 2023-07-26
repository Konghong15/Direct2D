#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class IUpdateable : public IBaseInterface
	{
	public:
		IUpdateable();
		virtual ~IUpdateable();

		virtual void Update(float deltaTime) = 0;
	};
}