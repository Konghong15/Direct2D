#pragma once

#include "OldTransformComponent.h"
#include "OldMovementComponent.h"
#include "OldRenderComponent.h"

namespace gameProcessor
{
	class RenderManager;
	class InputManager;
}

namespace componentBased
{
	class OldComponentObject
	{
	public:
		OldComponentObject(const OldTransformComponent& transformComponent, const OldMovementComponent& movementComponent, const OldRenderComponent& renderComponent);

		void Update(gameProcessor::InputManager* inputManager, float deltaTime);
		void Render(gameProcessor::RenderManager* renderManager);

	private:
		OldTransformComponent mTransformComponent;
		OldMovementComponent mMovementComponent;
		OldRenderComponent mRenderComponent;
	};
}