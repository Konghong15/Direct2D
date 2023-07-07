#include "Player.h"
#include "InputManager.h"
#include "RenderManger.h"
#include "Helper.h"

namespace camara
{
	Player::Player(const gameProcessor::hRectangle& rectangle, float speed)
		: GameObject(rectangle, speed)
		, mAttac
	{
		mDirection.SetXY(0, 1);
	}

	void Player::HandleInput(gameProcessor::InputManager* inputManager)
	{
		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
		{
			mSpeed = 500;
		}
		else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
		{
			mSpeed = -250;
		}
		else
		{
			mSpeed = 0;
		}

		if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
		{
			mDirection.Rotate(0.01);
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
		{
			mDirection.Rotate(-0.01);
		}
	}
}