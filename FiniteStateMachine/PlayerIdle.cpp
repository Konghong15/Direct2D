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
		// 몬스터의 공격에 충돌이 있었는지 체크

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
			// 가장 가까운 적을 탐색해서 그쪽 방향으로 공격함
			//	player->mWeapon->Action();
		}
	}
}