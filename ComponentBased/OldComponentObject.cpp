#include "OldComponentObject.h"

namespace componentBased
{
	OldComponentObject::OldComponentObject(const OldTransformComponent& transformComponent, const OldMovementComponent& movementComponent, const OldRenderComponent& renderComponent)
		: mTransformComponent(transformComponent)
		, mMovementComponent(movementComponent)
		, mRenderComponent(renderComponent)
	{
	}

	void OldComponentObject::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		mMovementComponent.Update(inputManager, deltaTime);
		mTransformComponent.Update(inputManager, deltaTime);
		mRenderComponent.SetMatrix3X3(mMovementComponent.GetTransform() * mTransformComponent.GetTransform());
	}

	void OldComponentObject::Render(gameProcessor::RenderManager* renderManager)
	{
		mRenderComponent.Render(renderManager);
	}
}