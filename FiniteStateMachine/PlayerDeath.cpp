#include "AnimationInstance.h"
#include "PlayerDeath.h"
#include "Player.h"

namespace finiteStateMachine
{
	PlayerDeath::PlayerDeath()
		: PlayerState(ePlayerState::Death)
		, mDeathMoveSpeed(30.f)
	{
	}

	void PlayerDeath::HandleInput(gameProcessor::InputManager* inputManager)
	{
		// �ٽý��� ��ư
		// Idle�� ���� ���� ��ü�� �ٽý��� �޽��� ������
	}

	ePlayerState PlayerDeath::HandleState(Player* player)
	{
		return PlayerState::GetNextState();
	}

	void PlayerDeath::Enter(Player* player)
	{
		PlayerState::Enter(player);
		player->mDirection.Move(0, 1.f);
		player->mDirection.Normalize();
		mbIsDrop = false;
	}

	void PlayerDeath::Update(Player* player, float deltaTime)
	{
		if (!mbIsDrop && player->mAnimationInstnace->GetFrameIndex() == player->mAnimationInstnace->GetTotalFrameCount() / 2)
		{
			player->mDirection.Move(0, -1.f);
			player->mDirection.Normalize();
			mbIsDrop = true;
		}

		player->mTranslate.Move(player->mDirection.GetX() * mDeathMoveSpeed * deltaTime, player->mDirection.GetY() * mDeathMoveSpeed * deltaTime);
	}
}