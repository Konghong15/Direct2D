#include "Camara.h"
#include "GameObject.h"

namespace camara
{
	Camara::Camara(unsigned int width, unsigned int height, float speed, GameObject* ownerObjectOrNull)
		: mRectangle(0, 0, width, height)
		, mOrginTranslate(gameProcessor::Matrix3X3::GetTranslate(-mRectangle.GetWidth() / 2, -mRectangle.GetHeight() / 2)* gameProcessor::Matrix3X3::GetScale(1, -1))
		, mTransform(mOrginTranslate)
		, mSpeed(speed)
		, mScale(1.f)
		, mDirection(1, 0)
		, mOwnerObjectOrNull(ownerObjectOrNull)
	{
	}

	void Camara::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		if (mOwnerObjectOrNull != nullptr)
		{
			const gameProcessor::Vector2& CAMARA_CENTER = GetClippingRectangle().GetCenter();
			const gameProcessor::Vector2& OWNER_CENTER = (mOwnerObjectOrNull->GetWorldRectangle()).GetCenter();

			mTranslate.Move(OWNER_CENTER.GetX() - CAMARA_CENTER.GetX(), OWNER_CENTER.GetY() - CAMARA_CENTER.GetY());

			mDirection = mOwnerObjectOrNull->GetDirection();
			float temp = mDirection.GetX();
			mDirection.SetX(mDirection.GetY());
			mDirection.SetY(-temp);
		}
		else
		{
			const float MOVEMENT_AMOUNT = mSpeed * deltaTime;

			if (inputManager->GetKeyState('W') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(-mDirection.GetY() * MOVEMENT_AMOUNT, mDirection.GetX() * MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('S') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(-mDirection.GetY() * -MOVEMENT_AMOUNT, mDirection.GetX() * -MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('A') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(mDirection.GetX() * -MOVEMENT_AMOUNT, mDirection.GetY() * -MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('D') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(mDirection.GetX() * MOVEMENT_AMOUNT, mDirection.GetY() * MOVEMENT_AMOUNT);
			}

			if (inputManager->GetKeyState('Q') == gameProcessor::eKeyState::Hold)
			{
				mDirection.Rotate(deltaTime);
			}
			else if (inputManager->GetKeyState('E') == gameProcessor::eKeyState::Hold)
			{
				mDirection.Rotate(-deltaTime);
			}
		}

		if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Hold)
		{
			mScale += deltaTime;
		}
		else if (inputManager->GetKeyState('C') == gameProcessor::eKeyState::Hold)
		{
			mScale -= deltaTime;

			if (mScale < 1.f)
			{
				mScale = 1.f;
			}
		}
		mTransform = mOrginTranslate;

		mTransform = gameProcessor::Matrix3X3::ComineMatrix(4
			, mTransform
			, gameProcessor::Matrix3X3::GetScale(mScale, mScale)
			, gameProcessor::Matrix3X3::GetRotate(mDirection.GetX(), mDirection.GetY())
			, gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}
}