#include "PlayerIdle.h"
#include "InputManager.h"
#include "Player.h"
#include "AnimationInstance.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	PlayerIdle::PlayerIdle()
		: PlayerState(ePlayerState::Idle)
	{
	}

	void PlayerIdle::HandleInput(gameProcessor::InputManager* inputManager)
	{
		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Push
			|| inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Push
			|| inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Push
			|| inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Push)
		{
			PlayerState::SetNextState(ePlayerState::Move);
		}

		mbIsAttack = inputManager->GetKeyState('X') == gameProcessor::eKeyState::Push;
	}

	ePlayerState PlayerIdle::HandleState(Player* player)
	{
		// ������ ���ݿ� �浹�� �־����� üũ

		return PlayerState::GetNextState();
	}

	void PlayerIdle::Enter(Player* player)
	{
		PlayerState::Enter(player);
		mbIsAttack = false;
	}

	void PlayerIdle::Update(Player* player, float deltaTime)
	{
		player->mAnimationInstnace->Update(deltaTime);

		if (mbIsAttack)
		{
			// ���� ����� ���� Ž���ؼ� ���� �������� ������
			//	player->mWeapon->Action();
		}
	}
}