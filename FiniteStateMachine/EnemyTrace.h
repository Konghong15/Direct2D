#pragma once

#include "EnemyState.h"
#include "Player.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyTrace : public EnemyState
	{
	public:
		EnemyTrace() : EnemyState(eEnemyState::Trace) {}

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
			if (enemy->mbAttack)
			{
				return eEnemyState::Attack;
			}

			return GetState();
		}

		virtual void Update(Enemy* enemy, float deltaTime) override
		{
			enemy->mTranslate += enemy->mDirection * enemy->mSpeed * deltaTime;
			EnemyState::Update(enemy, deltaTime);
		}
	};
}