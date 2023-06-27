#pragma once

#include "hRectangle.h"
#include "Component.h"

namespace entityComponentSystem
{
	struct RenderComponent : public Component
	{
		RenderComponent(const gameProcessor::hRectangle& rectangle)
			: Component(eComponentType::Render)
			, Rectangle(rectangle)
		{
		}

		gameProcessor::hRectangle Rectangle;
		// 애니메이션 인스턴스나 비트맵, shape오브젝트에서 다룬 것들
	};
}