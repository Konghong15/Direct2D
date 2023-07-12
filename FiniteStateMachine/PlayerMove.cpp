#include "PlayerMove.h"
#include "Player.h"
#include "InputManager.h"
#include "AnimationInstance.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	PlayerMove::PlayerMove()
		: PlayerState(ePlayerState::Move)
	{
	}

	void PlayerMove::OnHandleEvent(Player* player, const std::string& event, const std::string& data)
	{
		if (event == "collisionEnemy")
		{
			player->SetIsAlive(false);
			return;
		}
		if (event == "attack")
		{
			player->mbIsAttack = true;
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
			mbIsInput = true;

			return;
		}
	}

	ePlayerState PlayerMove::UpdateState(Player* player)
	{
		if (player->mbIsAlive == false)
		{
			return ePlayerState::Death;
		}
		if (player->mAcceleration < -player->mSpeed)
		{
			return ePlayerState::Idle;
		}

		return GetState();
	}

	void PlayerMove::Enter(Player* player)
	{
		PlayerState::Enter(player);
	}

	void PlayerMove::Update(Player* player, float deltaTime)
	{
		if (mbIsInput)
		{
			if (player->mDirection.Dot(player->mVelocity) < 0)
			{
				player->mVelocity = player->mDirection;
			}

			player->mAcceleration += player->mAccelerationIncrement * deltaTime;
		}
		else
		{
			player->mAcceleration -= player->mAccelerationIncrement * deltaTime * 5;
		}

		if (player->mAcceleration > player->mMaxAcceleration)
		{
			player->mAcceleration = player->mMaxAcceleration;
		}

		player->mVelocity += player->mDirection * (player->mSpeed + player->mAcceleration) * deltaTime;
		player->mTranslate.Move(player->mVelocity.GetX() * deltaTime, player->mVelocity.GetY() * deltaTime);

		PlayerState::Update(player, deltaTime);
		mbIsInput = false;
	}

	void PlayerMove::Exit(Player* player)
	{
		PlayerState::Exit(player);
		player->mVelocity.SetXY(0, 0);
	}
}