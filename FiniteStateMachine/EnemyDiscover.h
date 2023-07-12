#pragma once

#include "EnemyState.h"
#include "Player.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyDiscover : public EnemyState
	{
	public:
		EnemyDiscover() : EnemyState(eEnemyState::Discover) {}

		virtual eEnemyState UpdateState(Enemy* enemy) override
		{
			if (!enemy->mPlayer->GetIsAlive() && enemy->mAnimationInstnace->GetIsLastFrame())
			{
				return eEnemyState::Idle;
			}
			if (!enemy->mbIsAlive)
			{
				return eEnemyState::Death;
			}
			if (enemy->mAnimationInstnace->GetIsEnd())
			{
				return eEnemyState::Trace;
			}

			return GetState();
		}
	};
}