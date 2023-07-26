#pragma once

#include "IBaseInterface.h"

namespace d2dFramework
{
	class RenderManager;

	class IRenderable : public IBaseInterface
	{
	public:
		IRenderable();
		virtual ~IRenderable();

		virtual void Render(RenderManager* renderManager) = 0;
	};
}