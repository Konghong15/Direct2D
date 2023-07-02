#include "MovementComponent.h"

namespace entityCamara
{
	MovementComponent::MovementComponent(unsigned int entityId, const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration)
		: Component(entityId, eComponentType::Movement)
		, mVelocity(0, 0)
		, mDirection(direction)
		, mSpeed(speed)
		, mAcceleration(0.f)
		, mAccelerationIncrement(accelerationIncrement)
		, mMaxAcceleration(maxAcceleration)
	{
	}

	void MovementComponent::Update(float deltaTime)
	{
		if (mAcceleration > mMaxAcceleration)
		{
			mAcceleration = mMaxAcceleration;
		}

		mVelocity = mDirection * mSpeed * mAcceleration * deltaTime;
	}
}