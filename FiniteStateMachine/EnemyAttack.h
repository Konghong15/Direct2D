#pragma once

#include "EnemyState.h"
#include "Player.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyAttack : public EnemyState
	{
	public:
		EnemyAttack() : EnemyState(eEnemyState::Attack) {}

		virtual eEnemyState UpdateState(Enemy* enemy) override
		{
			if (!enemy->mbIsAlive)
			{
				return eEnemyState::Death;
			}
			if (enemy->mbIsProgressAttack && enemy->mWeapon->GetState() == eWeaponState::Idle)
			{
				return eEnemyState::Trace;
			}
			if (!enemy->mPlayer->GetIsAlive() && enemy->mWeapon->GetState() == eWeaponState::Idle)
			{
				return eEnemyState::Idle;
			}

			return GetState();
		}

		virtual void Update(Enemy* enemy, float deltaTime) override
		{
			if (!enemy->mbIsProgressAttack)
			{
				enemy->mAnimationInstnace->Update(deltaTime);
			}
			if (enemy->mAnimationInstnace->GetIsLastFrame())
			{
				enemy->mbIsProgressAttack = true;
				enemy->mWeapon->Action(enemy->mDirection);
			}

			enemy->mWeapon->HandleState();

			enemy->mTransform = enemy->combineMatrix();

			if (enemy->mParent != nullptr)
			{
				enemy->mTransform *= enemy->mParent->GetTrasform();
			}

			for (Object* child : enemy->mChildren)
			{
				child->Update(deltaTime);
			}
		}

		virtual void Exit(Enemy* enemy) override
		{
			EnemyState::Exit(enemy);
			enemy->mbIsProgressAttack = false;
		}
	};
}