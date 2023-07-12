#pragma once

#include "EnemyState.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyDeath : public EnemyState
	{
	public:
		EnemyDeath() : EnemyState(eEnemyState::Death) {}

		virtual eEnemyState UpdateState(Enemy* enemy) override
		{
			if (enemy->mAnimationInstnace->GetIsEnd())
			{
				return eEnemyState::Idle;
			}

			return EnemyState::GetState();
		}

		virtual void Exit(Enemy* enemy) override
		{
			EnemyState::Exit(enemy);
			int area = static_cast<int>(enemy->mPatrallArea.GetRadius());
			enemy->mTranslate.Move(rand() % area - area / 2, rand() % area - area / 2);
			enemy->mbIsAlive = true;
		}
	};
}