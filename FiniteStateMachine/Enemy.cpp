#include <cassert>

#include "AnimationInstance.h"
#include "Collision.h"
#include "Enemy.h"
#include "RenderManger.h"
#include "Player.h"
#include "Helper.h"
#include "Weapon.h"
#include "EnemyIdle.h"
#include "EnemyDiscover.h"
#include "EnemyTrace.h"
#include "EnemyAttack.h"
#include "EnemyDeath.h"

namespace finiteStateMachine
{
	Enemy::Enemy(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed, float patrallDistance, float attackDistance)
		: Object(rectangle, colliderArea)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mPlayer(nullptr)
		, mPatrallArea({ 0, 0 }, patrallDistance)
		, mAttackArea({ 0, 0 }, attackDistance)
		, mWeapon(weapon)
		, mbAttack(false)
		, mbPatrall(false)
		, mbIsProgressAttack(false)
		, mStates{ new EnemyIdle(), new EnemyDiscover(), new EnemyTrace(), new EnemyAttack(), new EnemyDeath() }
		, mCurrentState(mStates[static_cast<unsigned int>(eEnemyState::Idle)])
	{
	}

	Enemy::~Enemy()
	{
		delete mAnimationInstnace;

		for (int i = 0; i < static_cast<int>(eEnemyState::Size); ++i)
		{
			delete mStates[i];
		}
	}

	void Enemy::Update(float deltaTime)
	{
		mCurrentState->Update(this, deltaTime);
		eEnemyState nextState = mCurrentState->UpdateState(this);

		if (nextState != mCurrentState->GetState())
		{
			mCurrentState->Exit(this);
			mCurrentState = mStates[static_cast<unsigned int>(nextState)];
			mCurrentState->Enter(this);
		}
	}

	void Enemy::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		mAnimationInstnace->Render(renderManager, mRectangle, gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mDirection.GetX() <= 0 ? 1 : -1, -1), mTransform, compositeTrasform));
		D2D1_COLOR_F color = mbPatrall ? gameProcessor::Helper::GetRGBA(255, 0, 0, 180) : gameProcessor::Helper::GetRGBA(0, 0, 0, 80);
		renderManager->DrawCircle(mPatrallArea, mTransform * compositeTrasform, color);
		color = mbAttack ? gameProcessor::Helper::GetRGBA(255, 0, 0, 180) : gameProcessor::Helper::GetRGBA(0, 0, 0, 80);
		renderManager->DrawCircle(mAttackArea, mTransform * compositeTrasform, color);
		color = gameProcessor::Helper::GetRGBA(255, 0, 255, 80);
		renderManager->FillCircle(mCollider, mTransform * compositeTrasform, color);
		color = gameProcessor::Helper::GetRGBA(255, 0, 255, 255);
		renderManager->DrawCircle(mCollider, mTransform * compositeTrasform, color);

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}