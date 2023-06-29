#pragma once

#include "Vector2.h"
#include "Component.h"

namespace entityComponentSystem
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(unsigned int entityId, const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration);
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = default;
		MovementComponent& operator=(const MovementComponent& other) = default;

		void Update(float deltaTime);

		inline const gameProcessor::Vector2& GetVelocity() const;
		inline void SetDirection(const gameProcessor::Vector2& direction);

	private:
		gameProcessor::Vector2 mVelocity;
		gameProcessor::Vector2 mDirection;
		float mSpeed;
		float mAcceleration;
		const float mAccelerationIncrement;
		const float mMaxAcceleration;
	};

	const gameProcessor::Vector2& MovementComponent::GetVelocity() const
	{
		return mVelocity;
	}

	void MovementComponent::SetDirection(const gameProcessor::Vector2& direction)
	{
		mDirection = direction;
	}
}