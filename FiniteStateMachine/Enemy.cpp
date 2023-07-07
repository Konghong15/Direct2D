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
	Enemy::Enemy(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, Weapon* weapon, float speed, float patrallDistance, float attackDistance)
		: Object(rectangle)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mEnemyState(eEnemyState::Idle)
		, mPlayer(nullptr)
		, mPatrallArea({ 0, 0 }, patrallDistance)
		, mAttackArea({ 0, 0 }, attackDistance)
		, mWeapon(weapon)
		, mbAttack(false)
		, mbPatrall(false)
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

		switch (mEnemyState)
		{
		case finiteStateMachine::eEnemyState::Idle:
			if (mbPatrall && mAnimationInstnace->GetIsEnd())
			{
				mEnemyState = eEnemyState::Discover;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(eEnemyState::Discover));
				mAnimationInstnace->SetFrameIndex(0);
				mAnimationInstnace->InitIsEnd();
			}
			break;
		case eEnemyState::Discover:
			if (mAnimationInstnace->GetIsEnd())
			{
				mEnemyState = eEnemyState::Trace;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(eEnemyState::Trace));
				mAnimationInstnace->SetFrameIndex(0);
			}
			break;
		case finiteStateMachine::eEnemyState::Trace:
			if (!mbPatrall)
			{
				mEnemyState = eEnemyState::Idle;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(eEnemyState::Idle));
				mAnimationInstnace->SetFrameIndex(0);
			}
			if (mbAttack)
			{
				mEnemyState = eEnemyState::Attack;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(eEnemyState::Attack));
				mAnimationInstnace->SetFrameIndex(0);
				mAnimationInstnace->InitIsEnd();
			}
			break;
		case finiteStateMachine::eEnemyState::Attack:
			if (mAnimationInstnace->GetIsEnd())
			{
				mWeapon->Action(mDirection);
				mEnemyState = eEnemyState::Trace;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(eEnemyState::Trace));
				mAnimationInstnace->SetFrameIndex(0);
				mAnimationInstnace->InitIsEnd();

				//int radius = static_cast<int>(mPatrallArea.GetRadius());
				//mTranslate.Move(rand() % radius - 250, rand() % radius - 250);
			}

			break;
		default:
			assert(false);
			break;
		}
	}

	void Enemy::Update(float deltaTime)
	{
		HandleState();
		mAnimationInstnace->Update(deltaTime);

		if (mEnemyState == eEnemyState::Trace)
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
		D2D1_COLOR_F color = mbPatrall ? gameProcessor::Helper::GetRGBA(255, 0, 0, 255) : gameProcessor::Helper::GetRGBA(0, 0, 0, 255);
		renderManager->DrawCircle(mPatrallArea, mTransform * compositeTrasform, color);
		color = mbAttack ? gameProcessor::Helper::GetRGBA(255, 0, 0, 255) : gameProcessor::Helper::GetRGBA(0, 0, 0, 255);
		renderManager->DrawCircle(mAttackArea, mTransform * compositeTrasform, color);

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}