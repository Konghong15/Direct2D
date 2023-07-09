#include "PlayerState.h"
#include "Player.h"
#include "AnimationInstance.h"

namespace finiteStateMachine
{
	PlayerState::PlayerState(ePlayerState state)
		: mState(state)
		, mNextState(state)
	{
	}

	void PlayerState::Enter(Player* player)
	{
		player->mAnimationInstnace->SetAnimationIndex(static_cast<int>(GetState()));
		mNextState = mState;
	}

	void PlayerState::Update(Player* player, float deltaTime)
	{
		player->mAnimationInstnace->Update(deltaTime);
		player->mTransform = player->combineMatrix();

		for (Object* child : player->mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void PlayerState::Exit(Player* player)
	{
		player->mAnimationInstnace->SetFrameIndex(0);
		player->mAnimationInstnace->InitIsEnd();
	}
}