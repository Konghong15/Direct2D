#pragma once

#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class InputManager;
}

namespace componentBased
{
	class OldMovementComponent
	{
	public:
		OldMovementComponent(const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration);

		void Update(gameProcessor::InputManager* inputManager, float deltaTime);

		inline const gameProcessor::Matrix3X3& GetTransform() const;

	private:
		gameProcessor::Vector2 mDirection;
		float mSpeed;
		float mAcceleration;
		const float mAccelerationIncrement;
		const float mMaxAcceleration;

		gameProcessor::Vector2 mTranslate;
	};

	const gameProcessor::Matrix3X3& OldMovementComponent::GetTransform() const
	{
		return gameProcessor::Matrix3X3::GetTranslate(mTranslate);
	}
}