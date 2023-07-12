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

	void PlayerIdle::OnHandleEvent(Player* player, const std::string& event, const std::string& data)
	{
		if (event == "collisionEnemy")
		{
			player->mbIsAlive = false;
			return;
		}
		if (event == "arrowKeyInput")
		{
			if (data == "left")
			{
				player->mDirection.Move(-1, 0);
				player->mbIsLeft = true;
			}
			else if (data == "right")
			{
				player->mDirection.Move(1, 0);
				player->mbIsLeft = false;
			}
			else if (data == "up")
			{
				player->mDirection.Move(0, 1);
			}
			else if (data == "down")
			{
				player->mDirection.Move(0, -1);
			}

			player->mDirection.Normalize();
			player->mAcceleration = player->mAccelerationIncrement;
			return;
		}
		if (event == "attack")
		{
			player->mbIsAttack = true;
			return;
		}
	}

	ePlayerState PlayerIdle::UpdateState(Player* player)
	{
		if (player->mbIsAlive == false)
		{
			return ePlayerState::Death;
		}
		if (player->mAcceleration >= 0)
		{
			return ePlayerState::Move;
		}

		return GetState();
	}

	void PlayerIdle::Enter(Player* player)
	{
		PlayerState::Enter(player);
	}

	void PlayerIdle::Update(Player* player, float deltaTime)
	{
		PlayerState::Update(player, deltaTime);
	}
}