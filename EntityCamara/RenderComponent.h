#pragma once

#include "hRectangle.h"
#include "Component.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class RenderManager;
}

namespace entityCamara
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(unsigned int entityId, const gameProcessor::hRectangle& rectangle);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = default;
		RenderComponent& operator=(const RenderComponent& other) = default;

		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& matrix = gameProcessor::Matrix3X3::Identity());

	private:
		gameProcessor::hRectangle mRectangle;
		//비트맵이나 뭐 애니메이션인스턴스
	};
}