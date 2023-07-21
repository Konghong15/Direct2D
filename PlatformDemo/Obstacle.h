#pragma once

#include "GameObject.h"
#include "RenderManger.h"

namespace platform
{
	class Obstacle : public gameProcessor::GameObject
	{
	public:
		Obstacle(const gameProcessor::hRectangle& rectangle)
			: GameObject(rectangle)
		{
		}
		virtual ~Obstacle() = default;

		virtual void Update(float deltaTime) override
		{
		}

		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform) override
		{
			renderManager->DrawRectangle(GetLocalRectangle(), GetTransformInfo().WorldTransform * transform);
		}
	};
}