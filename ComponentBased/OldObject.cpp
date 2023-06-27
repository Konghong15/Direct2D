#include "OldObject.h"
#include "InputManager.h"
#include "RenderManger.h"
#include "Helper.h"

namespace componentBased
{
	OldObject::OldObject(const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate, const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration, const gameProcessor::hRectangle& rectangle)
		: mScale(scale)
		, mRotateInRadian(rotateInRadian)
		, mTranslate(translate)
		, mDirection(direction)
		, mSpeed(speed)
		, mAcceleration(0.f)
		, mAccelerationIncrement(accelerationIncrement)
		, mMaxAcceleration(maxAcceleration)
		, mRectangle(rectangle)
	{
	}

	void OldObject::Update(gameProcessor::InputManager* inputManager, float deltaTime)
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

		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3u, gameProcessor::Matrix3X3::GetScale(mScale), gameProcessor::Matrix3X3::GetRotate(mRotateInRadian), gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}

	void OldObject::Render(gameProcessor::RenderManager* renderManager)
	{
		renderManager->DrawRectangle(mRectangle, mTransform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
	}
}