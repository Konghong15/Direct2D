#include "PlayerMove.h"
#include "Player.h"
#include "InputManager.h"
#include "AnimationInstance.h"

namespace finiteStateMachine
{
	PlayerMove::PlayerMove()
		: PlayerState(ePlayerState::Move)
	{
	}

	void PlayerMove::HandleInput(gameProcessor::InputManager* inputManager)
	{
		mbIsAttack = inputManager->GetKeyState('X') == gameProcessor::eKeyState::Push;

		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::None
			&& inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::None
			&& inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::None
			&& inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::None)
		{
			PlayerState::SetNextState(ePlayerState::Idle);

			return;
		}

		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetY(1);
		}
		else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
		{
			mDirection.SetY(-1);
		}
		else
		{
			mDirection.SetY(0);
		}
		if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
		{
			mbIsLeft = true;
			mDirection.SetX(-1);
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
		{
			mbIsLeft = false;
			mDirection.SetX(1);
		}
		else
		{
			mDirection.SetX(0);
		}

		mDirection.Normalize();
	}

	ePlayerState PlayerMove::HandleState(Player* player)
	{
		return PlayerState::GetNextState();
	}

	void PlayerMove::Enter(Player* player)
	{
		PlayerState::Enter(player);
		mDirection = player->mDirection;
		mbIsLeft = player->mbIsLeft;
		mbIsAttack = false;
	}

	void PlayerMove::Update(Player* player, float deltaTime)
	{
		player->mDirection = mDirection;
		player->mbIsLeft = mbIsLeft;

		player->mTranslate.Move(mDirection.GetX() * player->mSpeed * deltaTime, mDirection.GetY() * player->mSpeed * deltaTime);

		PlayerState::Update(player, deltaTime);
	}
}