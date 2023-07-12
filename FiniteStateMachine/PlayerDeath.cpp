#include "AnimationInstance.h"
#include "PlayerDeath.h"
#include "Player.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	PlayerDeath::PlayerDeath()
		: PlayerState(ePlayerState::Death)
		, mbIsRestart(false)
		, mbIsDrop(false)
	{
	}

	void PlayerDeath::OnHandleEvent(Player* player, const std::string& event, const std::string& data)
	{
		if (event == "restart")
		{
			mbIsRestart = true;
			return;
		}
	}

	ePlayerState PlayerDeath::UpdateState(Player* player)
	{
		if (mbIsRestart)
		{
			mbIsRestart = false;
			return ePlayerState::Idle;
		}

		return ePlayerState::Death;
	}

	void PlayerDeath::Enter(Player* player)
	{
		PlayerState::Enter(player);
		mbIsRestart = false;
		mbIsDrop = false;
	}

	void PlayerDeath::Update(Player* player, float deltaTime)
	{
		if (player->mAnimationInstnace->GetIsEnd())
		{
			return;
		}

		if (!mbIsDrop && player->mAnimationInstnace->GetFrameIndex() == player->mAnimationInstnace->GetTotalFrameCount() / 2)
		{
			player->mDirection.Move(0, -1.f);
			player->mDirection.Normalize();
			mbIsDrop = true;
		}

		player->mTranslate.Move(player->mDirection.GetX() * DEATH_MOVE_SPEED * deltaTime, player->mDirection.GetY() * DEATH_MOVE_SPEED * deltaTime);
		PlayerState::Update(player, deltaTime);
	}

	void PlayerDeath::Exit(Player* player)
	{
		PlayerState::Exit(player);
		player->mbIsAlive = true;
	}
}