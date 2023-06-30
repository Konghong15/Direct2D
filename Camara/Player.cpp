#include "Player.h"
#include "InputManager.h"
#include "RenderManger.h"
#include "Helper.h"

namespace camara
{
	Player::Player(const gameProcessor::hRectangle& rectangle, float speed)
		: GameObject(rectangle, speed)
	{
		mDirection.SetXY(0, 1);
	}

	void Player::HandleInput(gameProcessor::InputManager* inputManager)
	{
		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
		{
			mSpeed = 200;
		}
		else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
		{
			mSpeed = -100;
		}
		else
		{
			mSpeed = 0;
		}

		if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Push)
		{
			mDirection.Rotate(gameProcessor::Helper::DegreeToRadian(-90));
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Push)
		{
			mDirection.Rotate(gameProcessor::Helper::DegreeToRadian(90));
		}

		mDirection.Normalize();
	}

	void Player::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform, D2D1_COLOR_F color)
	{
		gameProcessor::Matrix3X3 combinedTrasform = gameProcessor::Matrix3X3::GetRotate(mDirection.GetX(), mDirection.GetY())
			* transform;

		GameObject::Render(renderManager, transform, color);
		//renderManager->DrawLine(gameProcessor::Vector2(0, 500), combinedTrasform, color);
	}
}