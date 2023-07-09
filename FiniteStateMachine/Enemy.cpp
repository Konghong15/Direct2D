#include <cassert>

#include "AnimationInstance.h"
#include "Collision.h"
#include "Enemy.h"
#include "RenderManger.h"
#include "Player.h"
#include "Helper.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	Enemy::Enemy(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed, float patrallDistance, float attackDistance)
		: Object(rectangle, colliderArea)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mEnemiesState(eEnemyState::Idle)
		, mPlayer(nullptr)
		, mPatrallArea({ 0, 0 }, patrallDistance)
		, mAttackArea({ 0, 0 }, attackDistance)
		, mWeapon(weapon)
		, mbAttack(false)
		, mbPatrall(false)
		, mbIsProgressAttack(false)
	{
	}

	Enemy::~Enemy()
	{
		delete mAnimationInstnace;
	}

	void Enemy::HandleState(void)
	{
		mDirection = mPlayer->GetWorldRectangle().GetCenter() - GetWorldRectangle().GetCenter();
		mDirection.Normalize();

		mbPatrall = gameProcessor::Collision::CheckPointToCircle(mPlayer->GetWorldRectangle().GetCenter(), mPatrallArea * mTransform);
		mbAttack = gameProcessor::Collision::CheckPointToCircle(mPlayer->GetWorldRectangle().GetCenter(), mAttackArea * mTransform);

		switch (mEnemiesState)
		{
		case finiteStateMachine::eEnemyState::Idle:
			if (mbPatrall && mAnimationInstnace->GetIsEnd())
			{
				changeState(eEnemyState::Discover);
			}
			break;
		case eEnemyState::Discover:
			if (mAnimationInstnace->GetIsEnd())
			{
				changeState(eEnemyState::Trace);
			}
			break;
		case finiteStateMachine::eEnemyState::Trace:
			if (!mbPatrall)
			{
				changeState(eEnemyState::Idle);
			}
			if (mbAttack)
			{
				changeState(eEnemyState::Attack);
			}
			break;
		case finiteStateMachine::eEnemyState::Attack:
			if (mbIsProgressAttack && mWeapon->GetState() == eWeaponState::Idle)
			{
				changeState(eEnemyState::Trace);
				mbIsProgressAttack = false;
			}
			else if (mAnimationInstnace->GetIsLastFrame())
			{
				mWeapon->Action(mDirection);
				mbIsProgressAttack = true;
			}
			break;
		case finiteStateMachine::eEnemyState::Death:
			if (mAnimationInstnace->GetIsEnd())
			{
				changeState(eEnemyState::Idle);
				int area = static_cast<int>(mPatrallArea.GetRadius());
				mTranslate.Move(rand() % area - area / 2, rand() % area - area / 2);
				mbIsAlive = true;
			}
			break;
		default:
			assert(false);
			break;
		}

		if (mEnemiesState != eEnemyState::Death && !mbIsAlive)
		{
			changeState(eEnemyState::Death);
			mbIsProgressAttack = false;
		}

		mWeapon->HandleState();
	}

	void Enemy::Update(float deltaTime)
	{
		if (!mbIsProgressAttack)
		{
			mAnimationInstnace->Update(deltaTime);
		}

		if (mEnemiesState == eEnemyState::Trace)
		{
			mTranslate.Move(mDirection.GetX() * mSpeed * deltaTime, mDirection.GetY() * mSpeed * deltaTime);
		}
		mTransform = combineMatrix();

		if (mParent != nullptr)
		{
			mTransform *= mParent->GetTrasform();
		}

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
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

	void Enemy::changeState(eEnemyState state)
	{
		mEnemiesState = state;
		mAnimationInstnace->SetAnimationIndex(static_cast<int>(state));
		mAnimationInstnace->SetFrameIndex(0);
		mAnimationInstnace->InitIsEnd();
	}
}