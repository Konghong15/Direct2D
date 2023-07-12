#pragma once

#include "eEnemyState.h"
#include "Enemy.h"

namespace finiteStateMachine
{
	class Enemy;

	class EnemyState
	{
	public:
		EnemyState(eEnemyState enemyState) : mState(enemyState) {}

		virtual void Enter(Enemy* enemy)
		{
			enemy->mAnimationInstnace->SetAnimationIndex(static_cast<unsigned int>(GetState()));
		}

		virtual eEnemyState UpdateState(Enemy* enemy) = 0;

		virtual void Update(Enemy* enemy, float deltaTime)
		{
			enemy->mWeapon->HandleState();
			enemy->mDirection = enemy->mPlayer->GetWorldRectangle().GetCenter() - enemy->GetWorldRectangle().GetCenter();
			enemy->mDirection.Normalize();

			enemy->mbPatrall = gameProcessor::Collision::CheckPointToCircle(enemy->mPlayer->GetWorldRectangle().GetCenter(), enemy->mPatrallArea * enemy->mTransform);
			enemy->mbAttack = gameProcessor::Collision::CheckPointToCircle(enemy->mPlayer->GetWorldRectangle().GetCenter(), enemy->mAttackArea * enemy->mTransform);

			enemy->mAnimationInstnace->Update(deltaTime);

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

		virtual void Exit(Enemy* enemy)
		{
			enemy->mAnimationInstnace->SetFrameIndex(0);
			enemy->mAnimationInstnace->InitIsEnd();
		}

		inline eEnemyState GetState() const;

	private:
		eEnemyState mState;
	};

	eEnemyState EnemyState::GetState() const
	{
		return mState;
	}
}