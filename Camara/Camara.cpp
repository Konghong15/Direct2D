#include "Camara.h"
#include "GameObject.h"

namespace camara
{
	Camara::Camara(unsigned int width, unsigned int height, float speed, GameObject* ownerObjectOrNull)
		: mRectangle(-static_cast<int>(width) / 2, -static_cast<int>(height) / 2, width / 2, height / 2)
		, mScreenTransform(gameProcessor::Matrix3X3::GetScale(1, -1)* gameProcessor::Matrix3X3::GetTranslate(mRectangle.GetWidth() / 2, mRectangle.GetHeight() / 2))
		, mTranslate(0, 0)
		, mXaxis(1, 0)
		, mScale(1.f)
		, mSpeed(speed)
		, mCamaraTransform(gameProcessor::Matrix3X3::Identity())
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

			const gameProcessor::Vector2& ownerDirection = mOwnerObjectOrNull->GetDirection();
			mXaxis.SetX(ownerDirection.GetY());
			mXaxis.SetY(-ownerDirection.GetX());
		}
		else
		{
			const float MOVEMENT_AMOUNT = mSpeed * deltaTime;

			if (inputManager->GetKeyState('W') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(-mXaxis.GetY() * MOVEMENT_AMOUNT, mXaxis.GetX() * MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('S') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(-mXaxis.GetY() * -MOVEMENT_AMOUNT, mXaxis.GetX() * -MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('A') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(mXaxis.GetX() * -MOVEMENT_AMOUNT, mXaxis.GetY() * -MOVEMENT_AMOUNT);
			}
			else if (inputManager->GetKeyState('D') == gameProcessor::eKeyState::Hold)
			{
				mTranslate.Move(mXaxis.GetX() * MOVEMENT_AMOUNT, mXaxis.GetY() * MOVEMENT_AMOUNT);
			}

			if (inputManager->GetKeyState('Q') == gameProcessor::eKeyState::Hold)
			{
				mXaxis.Rotate(deltaTime);
			}
			else if (inputManager->GetKeyState('E') == gameProcessor::eKeyState::Hold)
			{
				mXaxis.Rotate(-deltaTime);
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

		mCamaraTransform = gameProcessor::Matrix3X3::ComineMatrix(3
			, gameProcessor::Matrix3X3::GetScale(mScale, mScale)
			, gameProcessor::Matrix3X3::GetRotate(mXaxis.GetX(), mXaxis.GetY())
			, gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}
}