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
	};
}