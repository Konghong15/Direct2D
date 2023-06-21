#include "ShapeObject.h"
#include "InputManager.h"

namespace project2
{
	ShapeObject::ShapeObject(const gameProcessor::Vector2& center)
		: mbHover(false)
		, mbSelect(false)
		, mScale(gameProcessor::Matrix3X3::Identity())
		, mRotate(mScale)
		, mTranslate(mScale)
	{
		mTranslate.SetTranslate(center.GetX(), center.GetY());
	}

	void ShapeObject::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		using namespace gameProcessor;

		float speed = deltaTime * 100;

		if (inputManager->GetKeyState('W') == eKeyState::Hold)
		{
			mTranslate.AddTranslate(0, -speed);
		}
		else if (inputManager->GetKeyState('S') == eKeyState::Hold)
		{
			mTranslate.AddTranslate(0, speed);
		}
		else if (inputManager->GetKeyState('A') == eKeyState::Hold)
		{
			mTranslate.AddTranslate(-speed, 0);
		}
		else if (inputManager->GetKeyState('D') == eKeyState::Hold)
		{
			mTranslate.AddTranslate(speed, 0);
		}

		if (inputManager->GetKeyState('Z') == eKeyState::Hold)
		{
			mScale.AddScale(deltaTime, deltaTime);
		}
		else if (inputManager->GetKeyState('X') == eKeyState::Hold)
		{
			mScale.AddScale(-deltaTime, -deltaTime);
		}
	}
}