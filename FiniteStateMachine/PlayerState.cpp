#include "PlayerState.h"
#include "Player.h"
#include "AnimationInstance.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	PlayerState::PlayerState(ePlayerState state)
		: mState(state)
	{
	}

	void PlayerState::Enter(Player* player)
	{
		player->mAnimationInstnace->SetAnimationIndex(static_cast<int>(GetState()));
	}

	void PlayerState::Update(Player* player, float deltaTime)
	{
		player->mAnimationInstnace->Update(deltaTime);
		player->mTransform = player->combineMatrix();
		player->mWeapon->HandleState();

		if (player->mbIsAttack)
		{
			player->mWeapon->Action(player->mAttackDirection);
			player->mbIsAttack = false;
		}

		for (Object* child : player->mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void PlayerState::Exit(Player* player)
	{
		player->mAnimationInstnace->SetFrameIndex(0);
		player->mAnimationInstnace->InitIsEnd();
		player->mbIsAttack = false;
	}
}