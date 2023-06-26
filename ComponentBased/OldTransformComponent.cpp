#include "OldTransformComponent.h"
#include "InputManager.h"

namespace componentBased
{
	OldTransformComponent::OldTransformComponent(const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate)
		: mScale(scale)
		, mRotateInRadian(rotateInRadian)
		, mTranslate(translate)
	{
	}

	void OldTransformComponent::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		const float CAMARA_SPEED = 100 * deltaTime;
		if (inputManager->GetKeyState('W') == gameProcessor::eKeyState::Hold)
		{
			mTranslate.Move(0, -CAMARA_SPEED);
		}
		else if (inputManager->GetKeyState('S') == gameProcessor::eKeyState::Hold)
		{
			mTranslate.Move(0, CAMARA_SPEED);
		}
		else if (inputManager->GetKeyState('A') == gameProcessor::eKeyState::Hold)
		{
			mTranslate.Move(-CAMARA_SPEED, 0);
		}
		else if (inputManager->GetKeyState('D') == gameProcessor::eKeyState::Hold)
		{
			mTranslate.Move(CAMARA_SPEED, 0);
		}
		if (inputManager->GetKeyState('Q') == gameProcessor::eKeyState::Hold)
		{
			mScale.Move(-deltaTime, -deltaTime);
		}
		else if (inputManager->GetKeyState('E') == gameProcessor::eKeyState::Hold)
		{
			mScale.Move(deltaTime, deltaTime);
		}
		else if (inputManager->GetKeyState('R') == gameProcessor::eKeyState::Hold)
		{
			mRotateInRadian += deltaTime;
		}

		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3u, gameProcessor::Matrix3X3::GetScale(mScale), gameProcessor::Matrix3X3::GetRotate(mRotateInRadian), gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}
}