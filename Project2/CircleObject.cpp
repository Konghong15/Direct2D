#include "CircleObject.h"
#include "InputManager.h"
#include "Collision.h"
#include "RenderManger.h"

namespace project2
{
	CircleObject::CircleObject(const gameProcessor::Circle& circle)
		: ShapeObject(circle.GetCenter())
		, mCircle(circle)
	{
		const gameProcessor::Vector2& center = mCircle.GetCenter();

		mCircle.Move(-center.GetX(), -center.GetY());
	}

	void CircleObject::Update(gameProcessor::InputManager* inputManager, float deltaTime)
	{
		const gameProcessor::Vector2& mousePos = inputManager->GetMousePos();
		gameProcessor::Circle transformCircle(mCircle);
		transformCircle *= mTransform;
		ShapeObject::updateMatrix();

		mbHover = gameProcessor::Collision::CheckPointToCircle(mousePos, transformCircle);
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
	}

	void CircleObject::Render(gameProcessor::RenderManager* renderManager)
	{
		if (mbSelect)
		{
			renderManager->FillCircle(mCircle, mTransform, { 1,1,0,1 });
		}
		else if (!mbHover)
		{
			renderManager->DrawCircle(mCircle, mTransform, { 0,0,0,1 });
		}
		else
		{
			renderManager->DrawCircle(mCircle, mTransform, { 1,0,0,1 });
		}
	}
}