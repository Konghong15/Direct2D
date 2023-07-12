#pragma once

#include "EnemyState.h"
#include "Enemy.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyIdle : public EnemyState
	{
	public:
		EnemyIdle() : EnemyState(eEnemyState::Idle) {}

		virtual eEnemyState UpdateState(Enemy* enemy) override
		{
			if (!enemy->mPlayer->GetIsAlive())
			{
				return eEnemyState::Idle;
			}
			if (enemy->mbPatrall && enemy->mAnimationInstnace->GetIsEnd())
			{
				return eEnemyState::Discover;
			}

			return GetState();
		}


		virtual void Exit(Enemy* enemy) override
		{
			enemy->mAnimationInstnace->SetFrameIndex(0);
			enemy->mAnimationInstnace->InitIsEnd();
		}
	};
}