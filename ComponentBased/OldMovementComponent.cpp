#include "OldMovementComponent.h"
#include "InputManager.h"

namespace componentBased
{
	OldMovementComponent::OldMovementComponent(const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration)
		: mDirection(direction)
		, mSpeed(speed)
		, mAcceleration(0.f)
		, mMaxAcceleration(maxAcceleration)
		, mAccelerationIncrement(accelerationIncrement)
	{
	}

	void OldMovementComponent::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		const int CUR_SPEED = mSpeed + mAcceleration;
	
		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetXY(0, -1);
			mTranslate += mDirection * CUR_SPEED;
		}
		else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetXY(0, 1);
			mTranslate += mDirection * CUR_SPEED;
		}
		else if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetXY(-1, 0);
			mTranslate += mDirection * CUR_SPEED;
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetXY(1, 0);
			mTranslate += mDirection * CUR_SPEED;
		}

		if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Hold)
		{
			mAcceleration += mAccelerationIncrement * deltaTime;
		}
		else
		{
			mAcceleration -= mAccelerationIncrement * deltaTime;

			if (mAcceleration < 0.f)
			{
				mAcceleration = 0.f;
			}
		}
	}
}