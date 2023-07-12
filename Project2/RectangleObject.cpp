#include "RectangleObject.h"
#include "InputManager.h"
#include "Collision.h"
#include "RenderManger.h"
#include "Helper.h"

namespace project2
{
	RectangleObject::RectangleObject(const gameProcessor::hRectangle& rectangle, float radian)
		: ShapeObject(rectangle.GetCenter())
		, mRectangle(rectangle)
		, mRadian(radian)
	{
		const gameProcessor::Vector2& center = rectangle.GetCenter();
		mRectangle.Move(-center.GetX(), -center.GetY());
	}

	void RectangleObject::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		const gameProcessor::Vector2& mousePos = inputManager->GetMousePos();
		gameProcessor::hRectangle transformRect(mRectangle * mTransform);
		ShapeObject::updateMatrix();

		mbHover = gameProcessor::Collision::CheckPointToRectangle(mousePos, transformRect);
		if (mbHover)
		{
			if (inputManager->GetKeyState(VK_LBUTTON) == gameProcessor::eKeyState::Push)
			{
				toggleSelect();
			}
		}

		if (!mbSelect)
		{
			return;
		}

		ShapeObject::Update(inputManager, deltaTime);

		if (inputManager->GetKeyState('Q') == gameProcessor::eKeyState::Hold)
		{
			mRadian += deltaTime;
			mRotate = gameProcessor::Matrix3X3::GetRotate(mRadian);
		}
		else if (inputManager->GetKeyState('E') == gameProcessor::eKeyState::Hold)
		{
			mRadian -= deltaTime;
			mRotate = gameProcessor::Matrix3X3::GetRotate(mRadian);
		}

	}

	void RectangleObject::Render(gameProcessor::RenderManager* renderManager)
	{
		if (mbSelect)
		{
			renderManager->FillRectangle(mRectangle, mTransform, gameProcessor::Helper::GetRGBA(255, 255, 0, 255));
		}
		else if (!mbHover)
		{
			renderManager->DrawRectangle(mRectangle, mTransform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
		}
		else
		{
			renderManager->DrawRectangle(mRectangle, mTransform, gameProcessor::Helper::GetRGBA(255, 0, 0, 255));
		}
	}
}